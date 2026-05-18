#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "../ALight.hpp"

class DirectionalLight : public ALight {
public:
    DirectionalLight(const LightParams &params);
    ~DirectionalLight() override = default;

    /**
     * Retrieves the inverse direction of the vector describing where the light points
     * (from the object toward the light), then normalizes it. It will be used for the shadow ray and
     * the light intensity calculation.
     */
    std::optional<Vec3> getLightDirection(const Vec3 &camHitPoint) const override;

    /**
     * To understand how much light a surface receives, i.e. its light intensity,
     * we need to look at Lambert's law in physics. First, let's
     * understand this law without any calculations.
     *
     * Imagine a sheet of paper under a lamp:
     *      lamp
     *        │
     *        │
     *        ▼
     *   ____________   ◀── flat sheet
     * => The sheet is well lit, the light hits it straight on.
     * ────────────────────────────────────────────────────────────
     * Now we tilt the sheet:
     *    lamp
     *      │
     *      │
     *      ▼
     *     /
     *    /
     *   /    ◀── tilted sheet
     * => Same lamp, but the sheet is less illuminated.
     * ────────────────────────────────────────────────────────────
     * We tilt even more:
     *   lamp
     *     │
     *     │
     *     ▼
     *     │
     *     │
     *     │  ◀── nearly vertical sheet
     * => The light comes from the side, the sheet receives almost nothing.
     *
     * Now let's derive the Lambert's law formula: L = kd * cos(θ) * I
     * Imagine a set of rays of width w hitting a surface at angle θ:
     *
     *   │ │ │ │ │   ◀── set of rays of width w, θ = 0°
     *   ▼ ▼ ▼ ▼ ▼
     *   ◀────────▶  ◀── w  (beam width)
     *   ──────────  ◀── w' (illuminated surface width)
     *   ◀ w = w' ▶  (no spreading because θ = 0°)
     * ────────────────────────────────────────────────────────────
     *   / / / / /   ◀── set of rays of width w, θ > 0°
     *   ↙ ↙ ↙ ↙ ↙
     *            /│
     *           / │
     *      w'  /  │ w
     *         /   │
     *        / θ  │
     *       /─────┘
     *       ▲
     *       w' : illuminated surface width (w' > w)
     *   ───────────────  ◀── surface
     *
     * First we look for w' to compute the energy per unit area. For this we use
     * the right triangle formula: cos(θ) = adjacent side / hypotenuse
     * => cos(θ) = w / w'
     * => w' = w / cos(θ)
     *
     * Once we have w', we can compute the energy per unit area: I / w'
     * Given that I is the total energy emitted by the light source over the set of rays of
     * width w and w' is the illuminated surface width. We know that w' = w / cos(θ)
     * so we substitute it in the calculation:
     * => I / w' = I / (w / cos(θ))
     * Dividing by a fraction = multiplying by its reciprocal:
     * => I * cos(θ) / w
     * Since w is constant (the beam width never changes), we ignore w:
     * => I * cos(θ)
     *
     * To compute cos(θ), we use the dot product between two unit vectors:
     * - N̂ : the surface normal at the point where the ray hits the surface (perpendicular to the surface)
     * - L̂ : the direction from the point where the ray hits the surface toward the light source
     *
     *          L̂   N̂
     *           \  │
     *            \ │
     *          θ  \│
     * ─────────────\───────  ◀── surface
     *
     * => N̂ · L̂ = ||N̂|| · ||L̂|| · cos(θ)
     * => N̂ · L̂ = 1 · 1 · cos(θ)
     * => N̂ · L̂ = cos(θ)
     *
     * Now let's determine kd which is simply the surface color
     * (in the raytracer's case, an RGB vector). We apply Lambert's law
     * separately on the 3 components (red, green, blue):
     * (R, G, B) * (N̂ · L̂) * I = (R * (N̂ · L̂) * I, G * (N̂ · L̂) * I, B * (N̂ · L̂) * I)
     *
     * Finally, assembling the final calculation to get the light intensity, the formula is:
     * L = (R, G, B) * (N̂ · L̂) * I = (R * (N̂ · L̂) * I, G * (N̂ · L̂) * I, B * (N̂ · L̂) * I)
     *     └───────┘   └─────┘   │
     *      colorRGB   cosTheta  _params.i
     */
    Vec3 getIntensity(const Vec3 &camHitPoint, const Vec3 &normal, const Vec3 &colorRGB,
        std::optional<Vec3> lightDir) const override;
private:
    LightParams _params;
};

#endif
