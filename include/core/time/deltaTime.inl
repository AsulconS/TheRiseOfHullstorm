static auto currentTime = std::chrono::steady_clock::now();
static auto lastTime = currentTime;
static auto timeSpan = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastTime);

static float getDeltaTime()
{
    currentTime = std::chrono::steady_clock::now();
    timeSpan = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastTime);
    lastTime = currentTime;
    return timeSpan.count();
}
