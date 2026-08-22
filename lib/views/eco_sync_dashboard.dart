import 'package:flutter/material.dart';
import '../controllers/dashboard_controller.dart';
import '../responsive.dart';
import 'widgets/metric_card.dart';
import 'widgets/actuator_card.dart';

class EcoSyncDashboard extends StatefulWidget {
  const EcoSyncDashboard({super.key});

  @override
  State<EcoSyncDashboard> createState() => _EcoSyncDashboardState();
}

class _EcoSyncDashboardState extends State<EcoSyncDashboard> {
  late final DashboardController controller;

  @override
  void initState() {
    super.initState();
    controller = DashboardController();
    controller.init();
  }

  @override
  void dispose() {
    controller.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: SafeArea(
        child: ListenableBuilder(
          listenable: controller,
          builder: (context, _) {
            if (controller.error != null) {
              return _buildErrorState(controller.error!);
            }
            return SingleChildScrollView(
              padding: Responsive.pagePadding(context),
              child: Center(
                child: ConstrainedBox(
                  constraints: const BoxConstraints(maxWidth: 1200),
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      _buildOverview(context, controller),
                      SizedBox(height: Responsive.sectionGap(context)),
                      _buildActuatorsOverview(context, controller),
                    ],
                  ),
                ),
              ),
            );
          },
        ),
      ),
    );
  }

  Widget _buildErrorState(String error) {
    return Center(
      child: Padding(
        padding: const EdgeInsets.all(24),
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            Icon(Icons.error_outline, color: Colors.red.shade400, size: 32),
            const SizedBox(height: 12),
            Text(
              error,
              textAlign: TextAlign.center,
              style: const TextStyle(color: Color(0xFF6B7280)),
            ),
            const SizedBox(height: 16),
            ElevatedButton(
              onPressed: () => controller.init(),
              child: const Text('Retry'),
            ),
          ],
        ),
      ),
    );
  }

  Widget _buildOverview(BuildContext context, DashboardController controller) {
    final isMobile = Responsive.isMobile(context);
    final reading = controller.sensorReading;

    final cards = [
      MetricCard(
        icon: Icons.thermostat_outlined,
        title: 'Temperature',
        value: '${reading.temperature.toStringAsFixed(1)}°',
        color: const Color(0xFFF97316),
      ),
      MetricCard(
        icon: Icons.water_drop_outlined,
        title: 'Humidity',
        value: '${reading.humidity.toStringAsFixed(0)}%',
        color: const Color(0xFF0EA5E9),
      ),
      MetricCard(
        icon: Icons.people_outline,
        title: 'Occupancy',
        value: '${reading.occupancy}',
        color: const Color(0xFF8B5CF6),
      ),
      MetricCard(
        icon: Icons.wb_sunny_outlined,
        title: 'LDR Difference',
        value: '${reading.ldrReading}',
        color: const Color(0xFFEAB308),
      ),
      MetricCard(
        icon: Icons.air_outlined,
        title: 'CO2 level',
        value: '${reading.co2Level} ',
        color: const Color(0xFF14B8A6),
      ),
    ];

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        const Text(
          'Room overview',
          style: TextStyle(
            fontSize: 18,
            fontWeight: FontWeight.w700,
            color: Color(0xFF111827),
          ),
        ),
        const SizedBox(height: 4),
        Text(
          'Current conditions and occupancy',
          style: TextStyle(fontSize: 13, color: Colors.grey.shade600),
        ),
        const SizedBox(height: 13),
        if (isMobile)
          Column(
            children: [
              for (int i = 0; i < cards.length; i++) ...[
                cards[i],
                if (i != cards.length - 1) const SizedBox(height: 10),
              ],
            ],
          )
        else
          Row(
            children: [
              for (int i = 0; i < cards.length; i++) ...[
                Expanded(child: cards[i]),
                if (i != cards.length - 1) const SizedBox(width: 10),
              ],
            ],
          ),
      ],
    );
  }

  Widget _buildActuatorsOverview(
    BuildContext context,
    DashboardController controller,
  ) {
    final isMobile = Responsive.isMobile(context);
    final actuators = controller.actuatorState;

    final cards = [
      ActuatorCard(
        icon: Icons.air_outlined,
        title: 'Fan speed',
        value: actuators.fanSpeed,
        color: const Color(0xFF2563EB),
        isManual: actuators.fanManualOverride,
        onChanged: controller.setFanSpeed,
        onModeChanged: controller.setFanMode,
      ),
      ActuatorCard(
        icon: Icons.light_mode_outlined,
        title: 'Light intensity',
        value: actuators.lightIntensity,
        color: const Color(0xFFEAB308),
        isManual: actuators.lightManualOverride,
        onChanged: controller.setLightIntensity,
        onModeChanged: controller.setLightMode,
      ),
    ];

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        const Text(
          'Actuators overview',
          style: TextStyle(
            fontSize: 18,
            fontWeight: FontWeight.w700,
            color: Color(0xFF111827),
          ),
        ),
        const SizedBox(height: 4),
        Text(
          'Room devices condition in real time.',
          style: TextStyle(fontSize: 13, color: Colors.grey.shade600),
        ),
        const SizedBox(height: 13),
        if (isMobile)
          Column(
            children: [
              for (int i = 0; i < cards.length; i++) ...[
                cards[i],
                if (i != cards.length - 1) const SizedBox(height: 10),
              ],
            ],
          )
        else
          Row(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              for (int i = 0; i < cards.length; i++) ...[
                Expanded(child: cards[i]),
                if (i != cards.length - 1) const SizedBox(width: 12),
              ],
            ],
          ),
      ],
    );
  }
}
