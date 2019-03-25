package com.luciangrigore;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class Main {
    private static Map<HeavenlyBody.Key, HeavenlyBody> solarSystem = new HashMap<>();
    private static Set<HeavenlyBody> planets = new HashSet<>();

    public static void main(String[] args) {
        //  Sets don't accept duplicates
        //  and are 'chaotic'
        //  HashSet almost like HashMap ( uses Hashes for each element )
        HeavenlyBody temp = new Planet("Mercury", 88);
        solarSystem.put(temp.getKey(), temp);
        planets.add(temp);

        temp = new Planet("Venus", 225);
        solarSystem.put(temp.getKey(), temp);
        planets.add(temp);

        temp = new Planet("Earth", 365);
        solarSystem.put(temp.getKey(), temp);
        planets.add(temp);

        HeavenlyBody tempMoon = new Moon("Moon", 27);
        solarSystem.put(tempMoon.getKey(), tempMoon);
        temp.addSatellite(tempMoon);

        temp = new Planet("Pluto", 248);
        solarSystem.put(temp.getKey(), temp);
        planets.add(temp);

        //  MORE PLANETS......

        System.out.println("Planets");
        for (HeavenlyBody planet : planets) {
            System.out.println("\t" + planet.toString());
        }

        HeavenlyBody body = solarSystem.get(HeavenlyBody.makeKey("Earth", HeavenlyBody.BodyType.PLANET));
        System.out.println("Moons of " + body.toString());
        for (HeavenlyBody earthMoon : body.getSatellites()) {
            System.out.println("\t" + earthMoon.toString());
        }


        Set<HeavenlyBody> moons = new HashSet<>();
        for (HeavenlyBody planet : planets) {
            moons.addAll(planet.getSatellites());
        }

        System.out.println("All moons ");
        for (HeavenlyBody moon : moons) {
            System.out.println("\t" + moon.toString());
        }

        //  Adds a different pluto planet ( different orbital period )
        //  this will not overwrite the originial entry
        HeavenlyBody pluto = new Planet("Pluto", 842);
        planets.add(pluto);

        for (HeavenlyBody planet : planets) {
            System.out.println(planet.toString());
        }
        System.out.println();

        pluto = new DwarfPlanet("Pluto", 842);
        planets.add(pluto);
        for (HeavenlyBody planet : planets) {
            System.out.println(planet.toString());
        }

        System.out.println("==============================");
        solarSystem.put(pluto.getKey(), pluto);
        solarSystem.put(pluto.getKey(), pluto);
        System.out.println(solarSystem.get(HeavenlyBody.makeKey("Pluto", HeavenlyBody.BodyType.PLANET)));
        System.out.println(solarSystem.get(HeavenlyBody.makeKey("Pluto", HeavenlyBody.BodyType.DWARF_PLANET)));


        System.out.println("==============================");
        pluto = new DwarfPlanet("Pluto", 9999);
        solarSystem.put(pluto.getKey(), pluto);
        System.out.println(solarSystem.get(HeavenlyBody.makeKey("Pluto", HeavenlyBody.BodyType.PLANET)));
        System.out.println(solarSystem.get(HeavenlyBody.makeKey("Pluto", HeavenlyBody.BodyType.DWARF_PLANET)));


        System.out.println("\n\n");
        System.out.println("Solar system contains:");
        for (HeavenlyBody test : solarSystem.values()) {
            //  Automatically uses the toString() method
            System.out.println("\t" + test);
        }
    }
}
