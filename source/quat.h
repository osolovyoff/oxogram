#pragma once

class Quat
{
public:
    Quat() = default;
    ~Quat() = default;

private:
    float w = { 1.0f };
    float x = { 0.0f };
    float y = { 0.0f };
    float z = { 0.0f };
};