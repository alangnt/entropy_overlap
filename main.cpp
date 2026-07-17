#include <iostream>
#include <numbers>
#include <cmath>

// Star:        R = 5
// Planet:      r = 3
// Separation:  d = 4

// First, we confirm we're in the partial case
// R - r = 2 and R + r = 8
// 2 < 4 < 8 -> Good

// Step 1. Locate the chords
// 1. Star
// x1 = ((d**2) + (R**2) - (r**2)) / (2 * d)
// x1 = (16 + 25 - 9) / 8
// x1 = 32 / 8
// x1 = 4
// 2. Planet
// x2 = d - x1
// x2 = 4 - 4
// x2 = 0

// Step 2. Find the height of the chord
// h = sqrt((R**2) - (x1**2))
// h = sqrt(25 - 16)
// h = sqrt(9)
// h = 3

// This means the circles cross at (4,+3) and (4,-3)
// Planet's center is (d,0) = (4,0) with r = 3
// This means they both genuinely pass across (4,3)

// Step 3. The two half-angles
// 1. Star
// θ_R = acos(x1 / R)
// θ_R = acos(4/5)
// θ_R = acos(0.8)
// θ_R = 0.6435rad (36.87°)
// 2. Planet
// θ_r = acos(x2 / r)
// θ_r = acos(0)
// θ_r = pi/2
// θ_r = 1.5708rad (90°)

// Step 4. Add the two segments
// R**2 * (θ − (sinθ * cosθ))
// 1. Star
// Star segment = 25 * (0.6435 - 0.6 * 0.8)
// Start segment = 4.09
// 2. Planet
// Planet segment = 9 * (1.5708 - 1 * 0)
// Planet segment = 14.14
// Overlap = 18.23

// Step 5. Cross-check
// Term 1. R**2. * acos((d**2 + R**2 − r**2) / (2 * d * R)) = 16.09
// Term 2. r**2 * acos((d**2 + r**2 − R**2) / (2 * d * r)) = 14.14
// Term 3. 1/2 * sqrt((−d + R + r)(d + R − r)(d − R + r)(d + R +r)) = 12.00
// 16.09 + 14.14 - 12.00 = 18.23

// Step 6. Apply to real metrics
// Blocked fraction = overlap / (pi * R**2)
// Blocked fraction = 18.22 / 78.54
// Blocked fraction = 0.232 = 23%

const double R = 5.0;
const double r = 3.0;
const double d = 4.0;

// Preliminary check
bool checkIfPartiallyOverlapping() {
  double distance1 = R - r;
  double distance2 = R + r;

  bool is_partially_overlapping = (distance1 < d) && (d < distance2);
  std::cout << "Partially Overlapping: " << is_partially_overlapping << std::endl;
  return is_partially_overlapping;
}

// Step 1
double locateStarChord() {
  // x1 = ((d**2) + (R**2) - (r**2)) / (2 * d)
  double x1 = ((d*d) + (R*R) - (r*r)) / (2 * d);
  return x1;
}
double locatePlanetChord(double x1) {
  double x2 = d - x1;
  return x2;
}

// Step 2
double calculateStarChordHeight(double x1) {
  // h = sqrt((R**2) - (x1**2))
  double h = std::sqrt((R*R) - (x1*x1));
  return h;
}

// Step 3
double calculateStarHalfAngle(double x1) {
  // θ_R = acos(x1 / R)
  double theta_R = std::acos(x1 / R);
  return theta_R;
}
double calculatePlanetHalfAngle(double x2) {
  // θ_r = acos(x2 / r)
  double theta_r = std::acos(x2 / r);
  return theta_r;
}

// Step 4
double calculateStarSegment(double theta_R) {
  // R**2 * (θ − (sinθ * cosθ))
  double star_segment = (R*R) * (theta_R - (std::sin(theta_R) * std::cos(theta_R)));
  return star_segment;
}
double calculatePlanetSegment(double theta_r) {
  // r**2 * (θ − (sinθ * cosθ))
  double planet_segment = (r*r) * (theta_r - (std::sin(theta_r) * std::cos(theta_r)));
  return planet_segment;
}

// Step 5
bool crossCheck(double theta_R, double theta_r, double h, double overlap) {
  // Term 1. R**2 * acos((d**2 + R**2 − r**2) / (2 * d * R))
  // or R**2 * θ_R
  // Term 2. r**2 * acos((d**2 + r**2 − R**2) / (2 * d * r))
  // or r**2 * θ_r
  // Term 3. 1/2 * sqrt((−d + R + r) * (d + R − r) * (d − R + r) * (d + R + r))
  // or d * h
  double term1 = (R*R) * theta_R;
  double term2 = (r*r) * theta_r;
  double term3 = d * h;

  double total_terms = term1 + term2 - term3;

  bool checks_out = std::fabs(total_terms - overlap) < 1e-9;

  std::cout << "Cross-check passes: " << std::boolalpha << checks_out << std::endl;

  return checks_out;
}

// Step 6
double calculateBlockedFraction(double overlap) {
  // Blocked fraction = overlap / (pi * R**2)
  double pi = std::numbers::pi;
  double blocked_fraction_raw = overlap / (pi * (R*R));
  double blocked_fraction = blocked_fraction_raw * 100;

  return blocked_fraction;
}

int main() {
  // Preliminary check
  bool is_partially_overlapping = checkIfPartiallyOverlapping();

  if (is_partially_overlapping == 1)
  {
    // Step 1
    double x1 = locateStarChord();
    double x2 = locatePlanetChord(x1);

    // Step 2
    double h = calculateStarChordHeight(x1);

    // Step 3
    double theta_R = calculateStarHalfAngle(x1);
    double theta_r = calculatePlanetHalfAngle(x2);

    // Step 4
    double star_segment = calculateStarSegment(theta_R);
    double planet_segment = calculatePlanetSegment(theta_r);
    double overlap = star_segment + planet_segment;

    // Step 5
    bool cross_check = crossCheck(theta_R, theta_r, h, overlap);

    // Step 6
    double blocked_fraction = calculateBlockedFraction(overlap);

    std::cout << "Blocked Fraction: " << blocked_fraction << "%" << std::endl;
    return 0;
  }
  else
  {
    // Check if totally overlapping
    double distance = R - r;
    bool is_totally_overlapping = d <= distance;

    if (is_totally_overlapping) {
      double blocked_fraction = (r / R) * (r / R);
      double blocked_percentage = blocked_fraction * 100;
      std::cout << "Blocked Fraction: " << blocked_percentage << "%" << std::endl;
      return 0;
    }
  }

  // If not overlapping at all
  std::cout << "Not overlapping" << std::endl;
  return 0;
}