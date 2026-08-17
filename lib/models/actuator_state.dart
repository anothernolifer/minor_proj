class ActuatorState {
  final double fanSpeed;
  final double lightIntensity;
  final bool fanManualOverride;
  final bool lightManualOverride;

  const ActuatorState({
    this.fanSpeed = 0,
    this.lightIntensity = 0,
    this.fanManualOverride = false,
    this.lightManualOverride = false,
  });

  /// Parses the JSON payload published by the ESP32:
  /// {"count":1,"temp":27.0,"humidity":55.0,"ldr":0,
  ///  "fan_speed":50,"light_intensity":75,
  ///  "fan_manual":false,"light_manual":false}
  factory ActuatorState.fromJson(Map<String, dynamic> json) {
    return ActuatorState(
      fanSpeed: (json['fan_speed'] as num?)?.toDouble() ?? 0,
      lightIntensity: (json['light_intensity'] as num?)?.toDouble() ?? 0,
      fanManualOverride: json['fan_manual'] as bool? ?? false,
      lightManualOverride: json['light_manual'] as bool? ?? false,
    );
  }

  ActuatorState copyWith({
    double? fanSpeed,
    double? lightIntensity,
    bool? fanManualOverride,
    bool? lightManualOverride,
  }) {
    return ActuatorState(
      fanSpeed: fanSpeed ?? this.fanSpeed,
      lightIntensity: lightIntensity ?? this.lightIntensity,
      fanManualOverride: fanManualOverride ?? this.fanManualOverride,
      lightManualOverride: lightManualOverride ?? this.lightManualOverride,
    );
  }
}
