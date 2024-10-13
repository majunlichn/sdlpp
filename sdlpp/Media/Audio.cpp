#include <sdlpp/Media/Audio.h>
#include <sdlpp/Core/Logging.h>

namespace sdl
{

std::vector<const char*> GetAudioDrivers()
{
    std::vector<const char*> drivers;
    int driverCount = SDL_GetNumAudioDrivers();
    if (driverCount > 0)
    {
        drivers.resize(driverCount);
        for (int i = 0; i < driverCount; ++i)
        {
            drivers[i] = SDL_GetAudioDriver(i);
        }
    }
    return drivers;
}

const char* GetCurrentAudioDriver()
{
    return SDL_GetCurrentAudioDriver();
}

std::vector<rad::Ref<AudioDevice>> EnumerateAudioPlaybackDevices()
{
    std::vector<rad::Ref<AudioDevice>> devices;
    int count = 0;
    const SDL_AudioDeviceID* ids = SDL_GetAudioPlaybackDevices(&count);
    if (count > 0)
    {
        devices.resize(count);
        for (int i = 0; i < count; ++i)
        {
            devices[i] = RAD_NEW AudioDevice(ids[i]);
        }
    }
    return devices;
}

std::vector<rad::Ref<AudioDevice>> EnumerateAudioRecordingDevices()
{
    std::vector<rad::Ref<AudioDevice>> devices;
    int count = 0;
    const SDL_AudioDeviceID* ids = SDL_GetAudioRecordingDevices(&count);
    if (count > 0)
    {
        devices.resize(count);
        for (int i = 0; i < count; ++i)
        {
            devices[i] = RAD_NEW AudioDevice(ids[i]);
        }
    }
    return devices;
}

bool LoadWAV(SDL_IOStream* src, bool close, SDL_AudioSpec* spec,
    Uint8** buffer, Uint32* sizeInBytes)
{
    bool result = SDL_LoadWAV_IO(src, close, spec, buffer, sizeInBytes);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_LoadWAV_IO failed: {}", SDL_GetError());
        return false;
    }
}

bool LoadWAVFromFile(std::string_view path, SDL_AudioSpec* spec,
    Uint8** buffer, Uint32* sizeInBytes)
{
    bool result = SDL_LoadWAV(path.data(), spec, buffer, sizeInBytes);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_LoadWAV failed: {}", SDL_GetError());
        return false;
    }
}

bool MixAudioData(Uint8* dst, const Uint8* src, SDL_AudioFormat format, Uint32 sizeInBytes, float volume)
{
    bool result = SDL_MixAudio(dst, src, format, sizeInBytes, volume);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_MixAudio failed: {}", SDL_GetError());
        return false;
    }
}

bool ConvertAudioData(const SDL_AudioSpec* srcSpec, const Uint8* srcData, int srcSizeInBytes,
    const SDL_AudioSpec* dstSpec, Uint8** dstData, int* dstSizeInBytes)
{
    bool result = SDL_ConvertAudioSamples(
        srcSpec, srcData, srcSizeInBytes, dstSpec, dstData, dstSizeInBytes);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_ConvertAudioSamples failed: {}", SDL_GetError());
        return false;
    }
}

AudioDevice::AudioDevice(SDL_AudioDeviceID id) :
    m_id(id)
{
    m_name = SDL_GetAudioDeviceName(id);
    bool result = SDL_GetAudioDeviceFormat(m_id, &m_format, &m_sampleFrames);
    if (result != true)
    {
        SDL_LOG(err, "SDL_GetAudioDeviceFormat failed: {}", SDL_GetError());
    }
}

AudioDevice::~AudioDevice()
{
}

bool AudioDevice::Open(const SDL_AudioSpec* spec)
{
    SDL_AudioDeviceID id = SDL_OpenAudioDevice(m_id, spec);
    if (id == m_id)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_OpenAudioDevice failed: {}", SDL_GetError());
        return false;
    }
}

bool AudioDevice::Pause()
{
    bool result = SDL_PauseAudioDevice(m_id);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_PauseAudioDevice failed: {}", SDL_GetError());
        return false;
    }
}

bool AudioDevice::Resume()
{
    bool result = SDL_ResumeAudioDevice(m_id);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_ResumeAudioDevice failed: {}", SDL_GetError());
        return false;
    }
}

bool AudioDevice::IsPaused()
{
    return (SDL_AudioDevicePaused(m_id) == true);
}

void AudioDevice::Close()
{
    SDL_CloseAudioDevice(m_id);
}

bool AudioDevice::BindStreams(SDL_AudioStream** streams, int streamCount)
{
    bool result = SDL_BindAudioStreams(m_id, streams, streamCount);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_BindAudioStreams failed: {}", SDL_GetError());
        return false;
    }
}

void AudioDevice::UnbindAudioStreams(SDL_AudioStream** streams, int streamCount)
{
    SDL_UnbindAudioStreams(streams, streamCount);
}

bool AudioDevice::BindStream(SDL_AudioStream* stream)
{
    bool result = SDL_BindAudioStream(m_id, stream);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_BindAudioStream failed: {}", SDL_GetError());
        return false;
    }
}

void AudioDevice::UnbindAudioStream(SDL_AudioStream* stream)
{
    SDL_UnbindAudioStream(stream);
}

bool AudioDevice::SetAudioPostmixCallback(SDL_AudioPostmixCallback callback, void* userData)
{
    bool result = SDL_SetAudioPostmixCallback(m_id, callback, userData);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_SetAudioPostmixCallback failed: {}", SDL_GetError());
        return false;
    }
}

rad::Ref<AudioStream> AudioStream::Create(const SDL_AudioSpec* srcSpec, const SDL_AudioSpec* dstSpec)
{
    SDL_AudioStream* handle = SDL_CreateAudioStream(srcSpec, dstSpec);
    if (handle)
    {
        return RAD_NEW AudioStream(handle);
    }
    else
    {
        SDL_LOG(err, "SDL_CreateAudioStream failed: {}", SDL_GetError());
        return nullptr;
    }
}

rad::Ref<AudioStream> AudioStream::Create(SDL_AudioDeviceID deviceID, const SDL_AudioSpec* spec,
    SDL_AudioStreamCallback callback, void* userData)
{
    SDL_AudioStream* stream = SDL_OpenAudioDeviceStream(deviceID, spec, callback, userData);
    if (stream)
    {
        return RAD_NEW AudioStream(stream);
    }
    else
    {
        SDL_LOG(err, "SDL_OpenAudioDeviceStream failed: {}", SDL_GetError());
        return nullptr;
    }
}

rad::Ref<AudioStream> AudioStream::CreateDefaultPlayback(const SDL_AudioSpec* spec)
{
    SDL_AudioStream* stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
        spec, nullptr, nullptr);
    if (stream)
    {
        return RAD_NEW AudioStream(stream);
    }
    else
    {
        SDL_LOG(err, "SDL_OpenAudioDeviceStream failed: {}", SDL_GetError());
        return nullptr;
    }
}

AudioStream::AudioStream(SDL_AudioStream* handle) :
    m_handle(handle)
{
    m_propID = SDL_GetAudioStreamProperties(m_handle);
    if (m_propID == 0)
    {
        SDL_LOG(err, "SDL_GetAudioStreamProperties failed: {}", SDL_GetError());
    }
}

AudioStream::~AudioStream()
{
    Destroy();
}

void AudioStream::Destroy()
{
    if (m_handle)
    {
        SDL_DestroyAudioStream(m_handle);
        m_handle = nullptr;
    }
}

bool AudioStream::GetFormat(SDL_AudioSpec* srcSpec, SDL_AudioSpec* dstSpec)
{
    return (SDL_GetAudioStreamFormat(m_handle, srcSpec, dstSpec) == 0);
}

bool AudioStream::SetFormat(const SDL_AudioSpec* srcSpec, const SDL_AudioSpec* dstSpec)
{
    return (SDL_SetAudioStreamFormat(m_handle, srcSpec, dstSpec) == 0);
}

float AudioStream::GetFrequencyRatio()
{
    return SDL_GetAudioStreamFrequencyRatio(m_handle);
}

bool AudioStream::SetFrequencyRatio(float ratio)
{
    return (SDL_SetAudioStreamFrequencyRatio(m_handle, ratio) == 0);
}

bool AudioStream::PutData(const void* data, int sizeInBytes)
{
    return (SDL_PutAudioStreamData(m_handle, data, sizeInBytes) == 0);
}

bool AudioStream::GetData(void* data, int sizeInBytes)
{
    return (SDL_GetAudioStreamData(m_handle, data, sizeInBytes));
}

int AudioStream::GetDataSizeAvailable()
{
    return SDL_GetAudioStreamAvailable(m_handle);
}

int AudioStream::GetDataSizeQueued()
{
    return SDL_GetAudioStreamQueued(m_handle);
}

bool AudioStream::Flush()
{
    bool result = SDL_FlushAudioStream(m_handle);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_FlushAudioStream failed: {}", SDL_GetError());
        return false;
    }
}

bool AudioStream::Clear()
{
    bool result = SDL_ClearAudioStream(m_handle);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_ClearAudioStream failed: {}", SDL_GetError());
        return false;
    }
}

bool AudioStream::Pause()
{
    bool result = SDL_PauseAudioStreamDevice(m_handle);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_PauseAudioStreamDevice failed: {}", SDL_GetError());
        return false;
    }
}

bool AudioStream::Resume()
{
    bool result = SDL_ResumeAudioStreamDevice(m_handle);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_ResumeAudioStreamDevice failed: {}", SDL_GetError());
        return false;
    }
}

bool AudioStream::Lock()
{
    bool result = SDL_LockAudioStream(m_handle);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_LockAudioStream failed: {}", SDL_GetError());
        return false;
    }
}

bool AudioStream::Unlock()
{
    bool result = SDL_UnlockAudioStream(m_handle);
    if (result == true)
    {
        return true;
    }
    else
    {
        SDL_LOG(err, "SDL_UnlockAudioStream failed: {}", SDL_GetError());
        return false;
    }
}

bool AudioStream::SetAudioStreamGetCallback(SDL_AudioStreamCallback callback, void* userData)
{
    return (SDL_SetAudioStreamGetCallback(m_handle, callback, userData) == 0);
}

bool AudioStream::SetAudioStreamPutCallback(SDL_AudioStreamCallback callback, void* userData)
{
    return (SDL_SetAudioStreamPutCallback(m_handle, callback, userData) == 0);
}

} // namespace sdl
