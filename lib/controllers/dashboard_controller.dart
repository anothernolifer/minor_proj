import 'package:flutter/foundation.dart';
import '../models/sensor_reading.dart';
import '../models/actuator_state.dart';
import '../services/mqtt_service.dart';

class DashboardController extends ChangeNotifier {
  final MqttService _mqttService;

  SensorReading _sensorReading = const SensorReading();
  ActuatorState _actuatorState = const ActuatorState();
  bool _isConnected = false;
  String? _error;

  DashboardController({MqttService? mqttService})
    : _mqttService = mqttService ?? MqttService();

  SensorReading get sensorReading => _sensorReading;
  ActuatorState get actuatorState => _actuatorState;
  bool get isConnected => _isConnected;
  String? get error => _error;

  Future<void> init() async {
    _mqttService.connectionStream.listen((connected) {
      _isConnected = connected;
      notifyListeners();
    });

    _mqttService.dataStream.listen((json) {
      _sensorReading = SensorReading.fromJson(json);
      // The ESP32 publishes one combined payload containing BOTH sensor
      // readings and the current actuator state (predicted or manual),
      // so both models parse from the same json.
      _actuatorState = ActuatorState.fromJson(json);
      notifyListeners();
    });

    try {
      await _mqttService.connect();
    } catch (e) {
      _error = 'Failed to connect to MQTT broker: $e';
      notifyListeners();
    }
  }

  void setFanSpeed(double value) {
    _actuatorState = _actuatorState.copyWith(
      fanSpeed: value,
      fanManualOverride: true,
    );
    notifyListeners();
    _mqttService.publishControl({'fan': value.toInt()});
  }

  void setLightIntensity(double value) {
    _actuatorState = _actuatorState.copyWith(
      lightIntensity: value,
      lightManualOverride: true,
    );
    notifyListeners();
    _mqttService.publishControl({'light': value.toInt()});
  }

  void setFanMode(bool isManual) {
    _actuatorState = _actuatorState.copyWith(fanManualOverride: isManual);
    notifyListeners();
    _mqttService.publishControl({'fan_mode': isManual ? 'manual' : 'auto'});
  }

  void setLightMode(bool isManual) {
    _actuatorState = _actuatorState.copyWith(lightManualOverride: isManual);
    notifyListeners();
    _mqttService.publishControl({'light_mode': isManual ? 'manual' : 'auto'});
  }

  @override
  void dispose() {
    _mqttService.dispose();
    super.dispose();
  }
}
