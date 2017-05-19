#pragma once

class Quat
{
public:
    const float heading = (rand() % 90 * M_PI) / 180;
    const float attitude = (rand() % 90 * M_PI) / 180;
    const float bank = (rand() % 90 * M_PI) / 180;

    Quat(const float heading, const float attitude, const float bank);
    Quat() = default;
    ~Quat() = default;

private:
    float w = { 1.0f };
    float x = { 0.0f };
    float y = { 0.0f };
    float z = { 0.0f };
};