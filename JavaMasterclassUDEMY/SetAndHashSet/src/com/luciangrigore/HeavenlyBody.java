package com.luciangrigore;

import java.util.HashSet;
import java.util.Set;

//  A final class cannot have subclasses
public class HeavenlyBody {

    private final double orbitalPeriod;
    private final Set<HeavenlyBody> satellites;
    private final Key key;

    public enum BodyType {
        STAR,
        PLANET,
        MOON,
        COMET,
        ASTEROID,
        DWARF_PLANET
    }

    public HeavenlyBody(String name, double orbitalPeriod, BodyType bodyType) {
        this.key = new Key(name, bodyType);
        this.orbitalPeriod = orbitalPeriod;
        this.satellites = new HashSet<>();
    }

    public Key getKey() {
        return key;
    }

    public double getOrbitalPeriod() {
        return orbitalPeriod;
    }

    public boolean addSatellite(HeavenlyBody moon) {
        return this.satellites.add(moon);
    }

    public Set<HeavenlyBody> getSatellites() {
        return new HashSet<HeavenlyBody>(this.satellites);
    }

    public static Key makeKey(String name, BodyType bodyType) {
        return new Key(name, bodyType);
    }

    //  Always overwrite the hashCode() method whenever we overwrite the equals() method
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if (obj instanceof HeavenlyBody) {
            HeavenlyBody heavenObj = (HeavenlyBody) obj;
            return this.key.equals(heavenObj.getKey());
        }

        return false;
    }

    @Override
    public int hashCode() {
        //  Won't be performance effective
        //  return 0;
        return this.key.hashCode();
    }

    @Override
    public String toString() {
        return this.key.name + ":" + this.key.bodyType + ":" + this.orbitalPeriod;
    }

    public static final class Key {
        private String name;
        private BodyType bodyType;

        private Key(String name, BodyType bodyType) {
            this.name = name;
            this.bodyType = bodyType;
        }

        public String getName() {
            return name;
        }

        public BodyType getBodyType() {
            return bodyType;
        }

        @Override
        public int hashCode() {
            return this.name.hashCode() + this.bodyType.hashCode() + 57;
        }

        @Override
        public boolean equals(Object obj) {
            Key key = (Key) obj;
            if (this.name.equals(key.getName())) {
                return this.bodyType == key.getBodyType();
            }
            return false;
        }
    }
}
