class SensorReading {
  final double temperature;
  final double humidity;
  final int occupancy; // "count" from ESP32
  final int ldrReading;
  final int co2Level;

  const SensorReading({
    this.temperature = 0,
    this.humidity = 0,
    this.occupancy = 0,
    this.ldrReading = 0,
    this.co2Level = 400,
  });

  /// Parses the JSON payload published by the ESP32:
  /// {"count":1,"temp":27.0,"humidity":55.0,"ldr":0,"co2":650}
  factory SensorReading.fromJson(Map<String, dynamic> json) {
    return SensorReading(
      temperature: (json['temp'] as num?)?.toDouble() ?? 0,
      humidity: (json['humidity'] as num?)?.toDouble() ?? 0,
      occupancy: (json['count'] as num?)?.toInt() ?? 0,
      ldrReading: (json['ldr'] as num?)?.toInt() ?? 0,
      co2Level: (json['co2'] as num?)?.toInt() ?? 0,
    );
  }

  SensorReading copyWith({
    double? temperature,
    double? humidity,
    int? occupancy,
    int? ldrReading,
    int? co2Level,
  }) {
    return SensorReading(
      temperature: temperature ?? this.temperature,
      humidity: humidity ?? this.humidity,
      occupancy: occupancy ?? this.occupancy,
      ldrReading: ldrReading ?? this.ldrReading,
      co2Level: co2Level ?? this.co2Level,
    );
  }
}
