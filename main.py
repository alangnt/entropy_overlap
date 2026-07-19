import pandas as pd

EARTH_RADIUS_METERS = 6.378 * (10**6)
SOLAR_RADIUS_METERS = 6.957 * (10**8)
PARSEC_METERS = 3.086 * (10**16)

exoplanets = pd.read_csv('data/exoplanets_archive.csv', comment='#')
exoplanets = exoplanets[exoplanets["default_flag"] == 1]

exo_existing_radii = exoplanets[["pl_name", "pl_rade", "st_rad", "sy_dist"]].dropna()

planet_radii_meters = exo_existing_radii["pl_rade"] * EARTH_RADIUS_METERS
stellar_radii_meters = exo_existing_radii["st_rad"] * SOLAR_RADIUS_METERS
distance_meters = exo_existing_radii["sy_dist"] * PARSEC_METERS

exo_existing_radii = exo_existing_radii.assign(
  pl_rade=planet_radii_meters,
  st_rad=stellar_radii_meters,
  sy_dist=distance_meters
)

print(exo_existing_radii.head())