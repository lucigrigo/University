package com.luciangrigore;

public class Planet extends HeavenlyBody {

    public Planet(String name, double orbitalPeriod) {
        super(name, orbitalPeriod, BodyType.PLANET);
    }

    @Override
    public boolean addSatellite(HeavenlyBody moon) {
        if (moon.getKey().getBodyType() == BodyType.MOON) {
            return super.addSatellite(moon);
        } else {
            return false;
        }
    }
}
