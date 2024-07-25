#ifndef TEXTURE
#define TEXTURE

#include <iostream>
#include <tuple>
#include <vector>
#include "Point.cpp"
#include "Ray.cpp"
#include "Sphere.cpp"
#include "Triangle.cpp"
#include "Light.cpp"
#include "Perlin.cpp"


vetor getMarbleColor(point& p, const PerlinNoise& perlin) {
    double scale = 10.0;
    double turbulence = 5.0;

    // Calculate noise value
    double noise = perlin.noise(p.getX() * scale, p.getY() * scale, p.getZ() * scale);

    // Apply a sine function to create marble veins
    double marble = sin(p.getX() * scale + turbulence * noise);

    // Map the sine value to a color range
    double t = (marble + 1.0) / 2.0; // Normalize to [0, 1]
    vetor color1(0.4f, 0.2f, 0.1f);  // Brown color
    vetor color2(1.0f, 1.0f, 1.0f);  // White color

    return color1 * t + color2 * (1.0 - t);
}

#include <cmath>

// Function to get the color at a point in space
vetor getCheckerboardColor(point& point) {
    // Scale factor to control the size of the checkers
    float scale = 1.0f;

    // Calculate the checkerboard pattern
    int check = (int(floor(point.getX() * scale)) +
                 int(floor(point.getY() * scale)) +
                 int(floor(point.getZ() * scale))) % 2;

    // Return black or white color based on the pattern
    if (check == 0) {
        return vetor(1.0f, 1.0f, 1.0f); // White
    } else {
        return vetor(0.0f, 0.0f, 0.0f); // Black
    }
}

vetor getCheckerboardColorSphere(sphere*& s, point& p){
    // Scale factor to control the size of the checkers
    float scale = 20.0f;

    vetor vec = s->sphere_map(p);

    // Calculate the checkerboard pattern
    int check = (int(floor(vec.getX() * scale)) +
                 int(floor(vec.getY() * scale)) +
                 int(floor(vec.getZ() * scale))) % 2;

    //if (check) std::clog << "check: " << check << std::flush;
    // Return black or white color based on the pattern
    if (check == 0) {
        return vetor(1.0f, 1.0f, 1.0f); // White
    } else {
        return vetor(0.0f, 0.0f, 0.0f); // Black
    }
}

vetor getWoodPattern(point& p, const PerlinNoise& perlin) {
    double scale = 2.0;
    double turbulence = 5.0;

    // Calculate noise value
    double noise = perlin.noise(p.getX() * scale, p.getY() * scale, p.getZ() * scale);

    // Apply a sine function to create wood rings
    double wood = sin(scale * (p.getX() + turbulence * noise));

    // Map the sine value to a color range
    double t = (wood + 1.0) / 2.0; // Normalize to [0, 1]
    vetor color1(0.6f, 0.3f, 0.1f);  // Dark brown
    vetor color2(0.9f, 0.7f, 0.5f);  // Light brown

    return color1 * t + color2 * (1.0 - t);
}




#endif