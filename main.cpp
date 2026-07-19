#include <iostream>
#include <numbers>
#include <cmath>
#include <limits>
#include <string>

// Input float number
static double requestFloatNumber(const std::string& request_input) {
  double float_number = 0.0;

  while (true) {
    std::cout << request_input << ": ";

    if (std::cin >> float_number) {
      break;
    }

    std::cout << "Invalid input. Please enter a valid float number.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  return float_number;
}

// Preliminary check
static bool checkIfPartiallyOverlapping(const double R, const double r, const double d) {
  const double distance1 = R - r;
  const double distance2 = R + r;

  const bool is_partially_overlapping = (distance1 < d) && (d < distance2);
  std::cout << "Partially Overlapping: " << is_partially_overlapping << std::endl;
  return is_partially_overlapping;
}

// Step 1
static double locateStarChord(const double R, const double r, const double d) {
  // x1 = ((d**2) + (R**2) - (r**2)) / (2 * d)
  const double x1 = ((d*d) + (R*R) - (r*r)) / (2 * d);
  return x1;
}
static double locatePlanetChord(const double d, const double x1) {
  const double x2 = d - x1;
  return x2;
}

// Step 2
static double calculateStarChordHeight(const double R, const double x1) {
  // h = sqrt((R**2) - (x1**2))
  const double h = std::sqrt((R*R) - (x1*x1));
  return h;
}

// Step 3
static double calculateStarHalfAngle(const double R, const double x1) {
  // θ_R = acos(x1 / R)
  const double theta_R = std::acos(x1 / R);
  return theta_R;
}
static double calculatePlanetHalfAngle(const double r, const double x2) {
  // θ_r = acos(x2 / r)
  const double theta_r = std::acos(x2 / r);
  return theta_r;
}

// Step 4
static double calculateStarSegment(const double R, const double theta_R) {
  // R**2 * (θ − (sinθ * cosθ))
  const double star_segment = (R*R) * (theta_R - (std::sin(theta_R) * std::cos(theta_R)));
  return star_segment;
}
static double calculatePlanetSegment(const double r, const double theta_r) {
  // r**2 * (θ − (sinθ * cosθ))
  const double planet_segment = (r*r) * (theta_r - (std::sin(theta_r) * std::cos(theta_r)));
  return planet_segment;
}

// Step 5
static bool crossCheck(const double R, const double r, const double d, const double theta_R, const double theta_r, const double h, const double overlap) {
  // Term 1. R**2 * acos((d**2 + R**2 − r**2) / (2 * d * R))
  // or R**2 * θ_R
  // Term 2. r**2 * acos((d**2 + r**2 − R**2) / (2 * d * r))
  // or r**2 * θ_r
  // Term 3. 1/2 * sqrt((−d + R + r) * (d + R − r) * (d − R + r) * (d + R + r))
  // or d * h
  const double term1 = (R*R) * theta_R;
  const double term2 = (r*r) * theta_r;
  const double term3 = d * h;

  const double total_terms = term1 + term2 - term3;

  const bool checks_out = std::fabs(total_terms - overlap) < 1e-9;

  std::cout << "Cross-check passes: " << std::boolalpha << checks_out << std::endl;

  return checks_out;
}

// Step 6
static double calculateBlockedFractionPercentage(const double R, const double overlap) {
  // Blocked fraction = overlap / (pi * R**2)
  constexpr double pi = std::numbers::pi;
  const double blocked_fraction_raw = overlap / (pi * (R*R));
  const double blocked_fraction = blocked_fraction_raw * 100;

  return blocked_fraction;
}

int main() {
  // Request R, r and d
  const double R = requestFloatNumber("Enter a value for R");
  const double r = requestFloatNumber("Enter a value for r");
  const double d = requestFloatNumber("Enter a value for d");

  // Preliminary check
  if (checkIfPartiallyOverlapping(R, r, d) == 1)
  {
    // Step 1
    const double x1 = locateStarChord(R, r, d);
    const double x2 = locatePlanetChord(d, x1);

    // Step 2
    const double h = calculateStarChordHeight(R, x1);

    // Step 3
    const double theta_R = calculateStarHalfAngle(R, x1);
    const double theta_r = calculatePlanetHalfAngle(r, x2);

    // Step 4
    const double star_segment = calculateStarSegment(R, theta_R);
    const double planet_segment = calculatePlanetSegment(r, theta_r);
    const double overlap = star_segment + planet_segment;

    // Step 5
    crossCheck(R, r, d, theta_R, theta_r, h, overlap);

    // Step 6
    const double blocked_fraction = calculateBlockedFractionPercentage(R, overlap);

    std::cout << "Blocked Fraction: " << blocked_fraction << "%" << std::endl;
    return 0;
  }

  // Check if totally overlapping
  if (d <= R - r) {
    const double blocked_fraction = (r / R) * (r / R);
    const double blocked_percentage = blocked_fraction * 100;
    std::cout << "Blocked Fraction: " << blocked_percentage << "%" << std::endl;
    return 0;
  }

  // If not overlapping at all
  std::cout << "Not overlapping" << std::endl;
  return 0;
}