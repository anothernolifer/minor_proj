import 'package:flutter/material.dart';

class Responsive {
  static const double mobileBreakpoint = 650;
  static const double tabletBreakpoint = 900;

  static bool isMobile(BuildContext context) {
    return MediaQuery.sizeOf(context).width < mobileBreakpoint;
  }

  static bool isTablet(BuildContext context) {
    final width = MediaQuery.sizeOf(context).width;

    return width >= mobileBreakpoint && width < tabletBreakpoint;
  }

  static bool isDesktop(BuildContext context) {
    return MediaQuery.sizeOf(context).width >= tabletBreakpoint;
  }

  static EdgeInsets pagePadding(BuildContext context) {
    if (isMobile(context)) {
      return const EdgeInsets.fromLTRB(16, 16, 16, 24);
    }

    if (isTablet(context)) {
      return const EdgeInsets.fromLTRB(24, 18, 24, 28);
    }

    return const EdgeInsets.fromLTRB(32, 18, 32, 28);
  }

  static double sectionGap(BuildContext context) {
    return isMobile(context) ? 24 : 28;
  }

  static double heroGap(BuildContext context) {
    return isMobile(context) ? 26 : 32;
  }

  static double heroTitleSize(BuildContext context) {
    if (isMobile(context)) {
      return 30;
    }

    return 34;
  }

  static double logoSize(BuildContext context) {
    return isMobile(context) ? 42 : 46;
  }

  static double logoTextSize(BuildContext context) {
    return isMobile(context) ? 26 : 28;
  }
}
