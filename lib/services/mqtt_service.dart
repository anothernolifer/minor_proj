import 'dart:async';
import 'dart:convert';

import 'package:mqtt_client/mqtt_client.dart';
import 'package:mqtt_client/mqtt_browser_client.dart';

class MqttService {
  final String broker;
  final int port;
  final String clientId;
  final String sensorTopic;
  final String controlTopic;

  MqttBrowserClient? _client;

  final _dataController = StreamController<Map<String, dynamic>>.broadcast();

  final _connectionController = StreamController<bool>.broadcast();

  MqttService({
    this.broker = 'broker.hivemq.com',

    // IMPORTANT:
    // Flutter Web uses MQTT over WebSocket.
    // HiveMQ WebSocket listener = 8000.
    this.port = 8000,

    this.clientId = 'flutter_dashboard',

    this.sensorTopic = 'esp32/sensordata',

    this.controlTopic = 'esp32/control',
  });

  // =====================================================
  // STREAMS
  // =====================================================

  Stream<Map<String, dynamic>> get dataStream => _dataController.stream;

  Stream<bool> get connectionStream => _connectionController.stream;

  // =====================================================
  // CONNECT
  // =====================================================

  Future<void> connect() async {
    // Generate a unique client ID.
    final uniqueClientId =
        '${clientId}_${DateTime.now().millisecondsSinceEpoch}';

    print('Connecting to MQTT WebSocket...');
    print('Broker: $broker');
    print('Port: $port');
    print('Client ID: $uniqueClientId');

    // ===================================================
    // MQTT BROWSER CLIENT
    // ===================================================

    _client = MqttBrowserClient('ws://$broker:$port/mqtt', uniqueClientId);

    _client!.port = port;

    _client!.logging(on: false);

    _client!.keepAlivePeriod = 20;

    _client!.autoReconnect = true;

    // ===================================================
    // CONNECTION CALLBACKS
    // ===================================================

    _client!.onConnected = () {
      print('MQTT connected!');

      _connectionController.add(true);
    };

    _client!.onDisconnected = () {
      print('MQTT disconnected!');

      _connectionController.add(false);
    };

    _client!.onAutoReconnect = () {
      print('MQTT auto reconnecting...');
    };

    _client!.onAutoReconnected = () {
      print('MQTT auto reconnected!');

      _connectionController.add(true);
    };

    // ===================================================
    // CONNECT MESSAGE
    // ===================================================

    final connMessage = MqttConnectMessage()
        .withClientIdentifier(uniqueClientId)
        .startClean();

    _client!.connectionMessage = connMessage;

    // ===================================================
    // CONNECT
    // ===================================================

    try {
      await _client!.connect();
    } catch (e) {
      print('MQTT connection exception: $e');

      _connectionController.add(false);

      _client!.disconnect();

      return;
    }

    // ===================================================
    // CHECK CONNECTION
    // ===================================================

    if (_client!.connectionStatus?.state == MqttConnectionState.connected) {
      print('MQTT connection successful');

      // =================================================
      // SUBSCRIBE TO ESP32 SENSOR DATA
      // =================================================

      _client!.subscribe(sensorTopic, MqttQos.atLeastOnce);

      print('Subscribed to: $sensorTopic');

      // =================================================
      // LISTEN FOR MQTT MESSAGES
      // =================================================

      _client!.updates!.listen((messages) {
        if (messages.isEmpty) {
          return;
        }

        final recMess = messages[0].payload as MqttPublishMessage;

        final payload = MqttPublishPayload.bytesToStringAsString(
          recMess.payload.message,
        );

        print('MQTT received: $payload');

        try {
          final decoded = jsonDecode(payload);

          if (decoded is Map<String, dynamic>) {
            _dataController.add(decoded);
          }
        } catch (e) {
          print('Invalid JSON received: $e');
        }
      });
    } else {
      print(
        'MQTT connection failed: '
        '${_client!.connectionStatus}',
      );

      _connectionController.add(false);
    }
  }

  // =====================================================
  // PUBLISH CONTROL COMMAND
  // =====================================================

  void publishControl(Map<String, dynamic> command) {
    if (_client?.connectionStatus?.state != MqttConnectionState.connected) {
      print('Cannot publish: MQTT not connected');

      return;
    }

    final builder = MqttClientPayloadBuilder();

    final jsonString = jsonEncode(command);

    builder.addString(jsonString);

    _client!.publishMessage(
      controlTopic,
      MqttQos.atLeastOnce,
      builder.payload!,
    );

    print('MQTT sent: $jsonString');
  }

  // =====================================================
  // CONVENIENCE METHODS
  // =====================================================

  void setFanSpeed(int speed) {
    speed = speed.clamp(0, 100);

    publishControl({'fan': speed});
  }

  void setLightIntensity(int intensity) {
    intensity = intensity.clamp(0, 100);

    publishControl({'light': intensity});
  }

  void setFanMode(bool manual) {
    publishControl({'fan_mode': manual ? 'manual' : 'auto'});
  }

  void setLightMode(bool manual) {
    publishControl({'light_mode': manual ? 'manual' : 'auto'});
  }

  // =====================================================
  // DISCONNECT / DISPOSE
  // =====================================================

  void dispose() {
    print('Disposing MQTT service...');

    _client?.disconnect();

    _dataController.close();

    _connectionController.close();
  }
}
