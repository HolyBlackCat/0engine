#include "audio.h"

#include <cstdio>
#include <fstream>

#include "lib_vorbis.h"
#include "lib_zlib.h"
#include "system.h"
#include "utils.h"

namespace Audio
{
    static ALCdevice *device;
    static ALCcontext *context;
    static ALCint freq, mono_srcs, stereo_srcs;

    struct SourceData
    {
        struct Attributes
        {
            SourceMode mode;

            float ref_distance, max_distance, rolloff_factor;

            float volume, pitch;

            fvec3 pos, vel;

            bool relative_position;
        };

        bool playing;

        bool play, stop;

        ALuint handle;
        bool full_update;
        bool container_dead;
        Attributes a, a_prev;
    };

    static Utils::Array<SourceData> mono_src_array, stereo_src_array;
    static Utils::PoolManager<int> mono_manager;
    static Utils::PoolManager<int> stereo_manager;

    static void PrepareAudioSettings(const char *txt, bool custom)
    {
        static auto Fail = [=]
        {
            if (custom)
                Sys::Error("Unable to parse OpenAL config.", "Fix command line switches. Use `--help` to get more information.");
            else
                Sys::Error("Unable to parse OpenAL config.");
        };
        static auto IsDigit = [&]()->bool{return *txt >= '0' && *txt <= '9';};
        static auto GetDigit = [&]()->int{return *txt - '0';};

        freq = 0;
        if (!IsDigit())
            Fail();
        do
        {
            freq = freq * 10 + GetDigit();
            txt++;
        }
        while (IsDigit());

        if (*(txt++) != ',')
            Fail();

        mono_srcs = 0;
        if (!IsDigit())
            Fail();
        do
        {
            mono_srcs = mono_srcs * 10 + GetDigit();
            txt++;
        }
        while (IsDigit());

        if (*(txt++) != '+')
            Fail();

        stereo_srcs = 0;
        if (!IsDigit())
            Fail();
        do
        {
            stereo_srcs = stereo_srcs * 10 + GetDigit();
            txt++;
        }
        while (IsDigit());

        if (*txt)
            Fail();
    }

    void Init()
    {
        ExecuteThisOnce();

        static constexpr int needed_openal_major = 1, needed_openal_minor = 1; // 1.1

        const char *config_str;
        if (Sys::CommandLineArgs::Check("lxsys-openal-config", &config_str))
            PrepareAudioSettings(config_str, 1);
        else
            PrepareAudioSettings(Sys::Config::openal_config.c_str(), 0);

        device = alcOpenDevice(0);
        if (!device)
        {
            if (Sys::CommandLineArgs::Check("lxsys-ignore-al-init-fail"))
                return;
            else
                Sys::Error("No valid audio device found.", "Try to change OpenAL settings using a command line switch. Use `--help` to get a list of them.");
        }

        ALCint openal_major, openal_minor;
        alcGetIntegerv(device, ALC_MAJOR_VERSION, 1, &openal_major);
        alcGetIntegerv(device, ALC_MINOR_VERSION, 1, &openal_minor);

        if (openal_major < needed_openal_major || (openal_major == needed_openal_major && openal_minor < needed_openal_minor))
            Sys::Error(Jo("Need OpenAL ", needed_openal_major, '.', needed_openal_minor, ", but found OpenAL ", openal_major, '.', openal_minor, '.'),
                       "Check if OpenAL32.dll is in the same folder as the executable and if it has correct version.\n"
                       "If you found any problems, reinstall the application. If it doesn't help, manually add the .dll.\n"
                       "Also, getting a new driver may help, especially if you got this error without having the .dll.");

        const ALCint config_array[] = {ALC_FREQUENCY, freq, ALC_MONO_SOURCES, mono_srcs, ALC_STEREO_SOURCES, stereo_srcs, 0};

        context = alcCreateContext(device, config_array);
        if (!context)
            Sys::Error("Found a valid audio device, but can't create OpenAL context.", "Try to change OpenAL settings using a command line switch. Use `--help` to get a list of them.");

        if (!alcMakeContextCurrent(context))
            Sys::Error("Audio context switching failed.");

        mono_manager.Resize(mono_srcs);
        stereo_manager.Resize(stereo_srcs);

        mono_src_array.Alloc(mono_srcs);
        stereo_src_array.Alloc(stereo_srcs);
    }
    void Cleanup()
    {
        ExecuteThisOnce();
        if (context)
            alcDestroyContext(context);
        if (device)
            alcCloseDevice(device);
    }

    void Tick()
    {
        #define LXINTERNAL_UPD(param, type_seq, al_enum, expr_postfix) if (data.a.param != data.a_prev.param) {data.a_prev.param = data.a.param; alSource##type_seq(data.handle, al_enum, data.a.param expr_postfix);}

        for (int i = 0; i < mono_manager.CurrentSize(); i++)
        {
            auto &data = mono_src_array[mono_manager.Pool()[i]];

            if (data.play)
            {
                data.play = 0;
                alSourcePlay(data.handle);
            }
            if (data.stop)
            {
                data.stop = 0;
                alSourceStop(data.handle);
            }

            ALint tmp;
            alGetSourcei(data.handle, AL_SOURCE_STATE, &tmp);
            data.playing = (tmp == AL_PLAYING);

            if (data.full_update)
            {
                data.full_update = 0;
                data.a_prev = data.a;
                alSourcef (data.handle, AL_REFERENCE_DISTANCE, data.a.ref_distance            );
                alSourcef (data.handle, AL_MAX_DISTANCE,       data.a.max_distance            );
                alSourcef (data.handle, AL_ROLLOFF_FACTOR,     data.a.rolloff_factor          );
                alSourcef (data.handle, AL_GAIN,               data.a.volume                  ); // These are for stereo srcs too.
                alSourcef (data.handle, AL_PITCH,              data.a.pitch                   ); //
                alSourcei (data.handle, AL_LOOPING,            data.a.mode == SourceMode::loop); //
                alSourcefv(data.handle, AL_POSITION,           data.a.pos.as_array()          );
                alSourcefv(data.handle, AL_VELOCITY,           data.a.vel.as_array()          );
                alSourcei (data.handle, AL_SOURCE_RELATIVE,    data.a.relative_position       );
            }

            if ((data.a.mode == SourceMode::loop) != (data.a_prev.mode == SourceMode::loop))
            {
                data.a_prev.mode = data.a.mode;
                alSourcei(data.handle, AL_LOOPING, data.a.mode == SourceMode::loop);
            }

            LXINTERNAL_UPD(ref_distance,      f, AL_REFERENCE_DISTANCE,   );
            LXINTERNAL_UPD(max_distance,      f, AL_MAX_DISTANCE,         );
            LXINTERNAL_UPD(rolloff_factor,    f, AL_ROLLOFF_FACTOR,       );
            LXINTERNAL_UPD(volume,            f, AL_GAIN,                 ); // These are for stereo srcs too.
            LXINTERNAL_UPD(pitch,             f, AL_PITCH,                ); //
            LXINTERNAL_UPD(pos,               fv, AL_POSITION, .as_array());
            LXINTERNAL_UPD(vel,               fv, AL_VELOCITY, .as_array());
            LXINTERNAL_UPD(relative_position, i, AL_SOURCE_RELATIVE,      );

            if (data.container_dead && (data.a.mode != SourceMode::once || data.playing == 0))
            {
                alDeleteSources(1, &data.handle);
                mono_manager.Free(mono_manager.Pool()[i--]);
            }
        }

        for (int i = 0; i < stereo_manager.CurrentSize(); i++)
        {
            auto &data = stereo_src_array[stereo_manager.Pool()[i]];

            if (data.play)
            {
                data.play = 0;
                alSourcePlay(data.handle);
            }
            if (data.stop)
            {
                data.stop = 0;
                alSourceStop(data.handle);
            }

            ALint tmp;
            alGetSourcei(data.handle, AL_SOURCE_STATE, &tmp);
            data.playing = (tmp == AL_PLAYING);

            if (data.full_update)
            {
                data.full_update = 0;
                data.a_prev = data.a;
                alSourcef (data.handle, AL_GAIN,               data.a.volume                  );
                alSourcef (data.handle, AL_PITCH,              data.a.pitch                   );
                alSourcei (data.handle, AL_LOOPING,            data.a.mode == SourceMode::loop);
            }

            if ((data.a.mode == SourceMode::loop) != (data.a_prev.mode == SourceMode::loop))
            {
                data.a_prev.mode = data.a.mode;
                alSourcei(data.handle, AL_LOOPING, data.a.mode == SourceMode::loop);
            }

            LXINTERNAL_UPD(volume,            f, AL_GAIN,                 );
            LXINTERNAL_UPD(pitch,             f, AL_PITCH,                );

            if (data.container_dead && (data.a.mode != SourceMode::once || data.playing == 0))
            {
                alDeleteSources(1, &data.handle);
                stereo_manager.Free(stereo_manager.Pool()[i--]);
            }
        }

        #undef LXINTERNAL_UPD

        ForceErrorCheck();
    }

    void ForceErrorCheck()
    {
        if (ALCenum err = alcGetError(device))
        {
            switch (err)
            {
                case ALC_INVALID_DEVICE:  Sys::Error("ALC: Invalid device.");
                case ALC_INVALID_CONTEXT: Sys::Error("ALC: Invalid context.");
                case ALC_INVALID_ENUM:    Sys::Error("ALC: Invalid enum.");
                case ALC_INVALID_VALUE:   Sys::Error("ALC: Invalid value.");
                case ALC_OUT_OF_MEMORY:   Sys::Error("ALC: Out of memory.");
                default:                  Sys::Error("ALC: Unknown error.");
            }
        }
    }

    void SoundData::LoadWAV(Utils::BinaryInput io)
    {
        Clear();

        auto ParseError    = [&](const char *txt){Exception::CantParse({io.Name(), txt});};

        unsigned char tmp;
        bool stereo;
        bool uses_16_bits;

        auto CheckByte     = [&](unsigned char byte, const char *error) {io.ReadEx(tmp); if (tmp != byte) ParseError(error);};

        uint32_t data_size, data_size_alt;

        CheckByte('R', "`RIFF` label is missing.");
        CheckByte('I', "`RIFF` label is missing.");
        CheckByte('F', "`RIFF` label is missing.");
        CheckByte('F', "`RIFF` label is missing.");
        io.ReadEx(tmp); data_size = tmp;
        io.ReadEx(tmp); data_size |= tmp << 8;
        io.ReadEx(tmp); data_size |= tmp << 16;
        io.ReadEx(tmp); data_size |= tmp << 24;
        data_size -= 36;
        CheckByte('W', "`WAVE` label is missing.");
        CheckByte('A', "`WAVE` label is missing.");
        CheckByte('V', "`WAVE` label is missing.");
        CheckByte('E', "`WAVE` label is missing.");
        CheckByte('f', "`fmt ` label is missing.");
        CheckByte('m', "`fmt ` label is missing.");
        CheckByte('t', "`fmt ` label is missing.");
        CheckByte(' ', "`fmt ` label is missing.");
        CheckByte(0x10, "A file must not contain any additional data.");
        CheckByte(0x00, "A file must not contain any additional data.");
        CheckByte(0x00, "A file must not contain any additional data.");
        CheckByte(0x00, "A file must not contain any additional data.");
        CheckByte(0x01, "A file must must be not compressed and must not use floating point samples.");
        CheckByte(0x00, "A file must must be not compressed and must not use floating point samples.");
        io.ReadEx(tmp);
        switch (tmp)
        {
            case 1: stereo = 0; break;
            case 2: stereo = 1; break;
            default: ParseError("A file must be mono or stereo. Larger amount of channels is not supported."); return;
        }
        CheckByte(0x00, "A file must be mono or stereo. Larger amount of channels is not supported.");
        io.ReadEx(tmp); freq = tmp;
        io.ReadEx(tmp); freq |= tmp << 8;
        io.ReadEx(tmp); freq |= tmp << 16;
        io.ReadEx(tmp); freq |= tmp << 24;
        io.SeekRel(6);
        io.ReadEx(tmp);
        switch (tmp)
        {
            case 8: uses_16_bits = 0; break;
            case 16: uses_16_bits = 1; break;
            default: ParseError("A file must have 8 or 16 bits per sample."); return;
        }
        CheckByte(0x00, "A file must have 8 or 16 bits per sample.");
        CheckByte('d', "`data` label is missing.");
        CheckByte('a', "`data` label is missing.");
        CheckByte('t', "`data` label is missing.");
        CheckByte('a', "`data` label is missing.");
        io.ReadEx(tmp); data_size_alt = tmp;
        io.ReadEx(tmp); data_size_alt |= tmp << 8;
        io.ReadEx(tmp); data_size_alt |= tmp << 16;
        io.ReadEx(tmp); data_size_alt |= tmp << 24;
        if (data_size != data_size_alt)
            ParseError("A file contains corrupted length data or contains an additional sections.");

        if (uses_16_bits)
            if (stereo)
                format = SoundFormat::stereo16;
            else
                format = SoundFormat::mono16;
        else
            if (stereo)
                format = SoundFormat::stereo8;
            else
                format = SoundFormat::mono8;

        switch (format)
        {
          case SoundFormat::stereo8:
            if (data_size % 2) ParseError("A file is 8 bits stereo, but data length is multiply of two.");
            break;
          case SoundFormat::mono16:
            if (data_size % 2) ParseError("A file is 16 bits mono, but data length is multiply of two.");
            break;
          case SoundFormat::stereo16:
            if (data_size % 4) ParseError("A file is 16 bits stereo, but data length is multiply of four.");
            break;
          default:
            break;
        }

        size = data_size / FormatBytesPerSample(format);

        data.Alloc(data_size);

        if (uses_16_bits)
        {
            for (uint32_t i = 0; i < data_size / 2; i++)
            {
                auto &ref = AtMono16(i);
                io.ReadEx(tmp);
                ref = tmp;
                io.ReadEx(tmp);
                ref |= tmp << 8;
            }
        }
        else
        {
            io.ReadEx<uint8_t>((uint8_t *)data, data_size);
        }
    }
    void SoundData::LoadOGG(Utils::BinaryInput io, bool load_as_8bit)
    {
        Clear();

        ov_callbacks callbacks;
        callbacks.tell_func = [](void *rwops) -> long
        {
            return ((SDL_RWops *)rwops)->seek((SDL_RWops *)rwops, 0, RW_SEEK_CUR);
        };
        callbacks.seek_func = [](void *rwops, int64_t offset, int mode) -> int
        {
            #if SEEK_SET != RW_SEEK_SET || SEEK_CUR != RW_SEEK_CUR || SEEK_END != RW_SEEK_END
            switch (mode)
            {
                case SEEK_SET: mode = RW_SEEK_SET; break;
                case SEEK_CUR: mode = RW_SEEK_CUR; break;
                case SEEK_END: mode = RW_SEEK_END; break;
            }
            #endif
            return ((SDL_RWops *)rwops)->seek((SDL_RWops *)rwops, offset, mode);
        };
        callbacks.read_func = [](void *dst, std::size_t sz, std::size_t count, void *rwops) -> std::size_t
        {
            return ((SDL_RWops *)rwops)->read((SDL_RWops *)rwops, dst, sz, count);
        };
        callbacks.close_func = 0;

        OggVorbis_File ogg_file;
        switch (ov_open_callbacks((void *)io.RWops(), &ogg_file, 0, 0, callbacks))
        {
          case 0:
            break;
          case OV_EREAD:
            Exception::CantParse({io.Name(), "Unable to read data from the stream."});
            break;
          case OV_ENOTVORBIS:
            Exception::CantParse({io.Name(), "This is not vorbis audio."});
            break;
          case OV_EVERSION:
            Exception::CantParse({io.Name(), "Vorbis version mismatch."});
            break;
          case OV_EBADHEADER:
            Exception::CantParse({io.Name(), "Invalid header."});
            break;
          case OV_EFAULT:
            Exception::CantParse({io.Name(), "Internal vorbis error."});
            break;
          default:
            Exception::CantParse({io.Name(), "Unknown vorbis error."});
            break;
        }
        // IMPORTANT: Below this line you must do `ov_clear(&ogg_file);` before returning or throwing anything.

        vorbis_info *info = ov_info(&ogg_file, -1);
        uint64_t samples = ov_pcm_total(&ogg_file, -1);
        if (samples > 0xffffffffu)
        {
            ov_clear(&ogg_file);
            Exception::CantParse({io.Name(), "The file is too big."});
        }

        freq = info->rate;

        switch (info->channels)
        {
          case 1:
            if (load_as_8bit)
                Empty(samples, SoundFormat::mono8);
            else
                Empty(samples, SoundFormat::mono16);
            break;
          case 2:
            if (load_as_8bit)
                Empty(samples, SoundFormat::stereo8);
            else
                Empty(samples, SoundFormat::stereo16);
            break;
          default:
            ov_clear(&ogg_file);
            Exception::CantParse({io.Name(), Jo("The file must be mono or stereo, but this one has ", info->channels, " channels.")});
            break;
        }

        uint32_t buf_len = samples * FormatBytesPerSample(format);
        char *buf = (char *)Data();

        int current_bitstream = -1;
        while (1)
        {
            if (buf_len == 0)
                break;
            int bitstream;
            long val = ov_read(&ogg_file, buf, buf_len, Utils::SysInfo::big_endian, load_as_8bit ? 1 : 2, !load_as_8bit, &bitstream);
            if (val == 0)
            {
                ov_clear(&ogg_file);
                Exception::CantParse({io.Name(), "Unexpected end of the stream."});
            }
            if (bitstream != current_bitstream)
            {
                current_bitstream = bitstream;
                vorbis_info *local_info = ov_info(&ogg_file, bitstream);
                if (local_info->channels != info->channels)
                {
                    ov_clear(&ogg_file);
                    Exception::CantParse({io.Name(), Jo("The amount of channels have changed from ", info->channels, " to ", local_info->channels, ". Dynamic amount of channels is not supported.")});
                }
                if (local_info->rate != info->rate)
                {
                    ov_clear(&ogg_file);
                    Exception::CantParse({io.Name(), Jo("The sampling rate have changed from ", info->rate, " to ", local_info->rate, ". Dynamic sampling rate is not supported.")});
                }
            }
            switch (val)
            {
              case OV_HOLE:
                ov_clear(&ogg_file);
                Exception::CantParse({io.Name(), "The file data is corrupted."});
                break;
              case OV_EBADLINK:
                ov_clear(&ogg_file);
                Exception::CantParse({io.Name(), "Bad link."});
                break;
              case OV_EINVAL:
                ov_clear(&ogg_file);
                Exception::CantParse({io.Name(), "Invalid header."});
                break;
              default:
                buf += val;
                buf_len -= val;
                break;
            }
        }

        ov_clear(&ogg_file);
    }
    void SoundData::SaveWAV(Utils::BinaryOutput io)
    {
        auto Byte = [&](uint8_t byte){io.WriteEx(byte);};
        auto Zero = [&](unsigned int len){while (len--) Byte(0x00);};
        auto Uint32 = [&](uint32_t x){Byte(x & 0xff); Byte((x >> 8) & 0xff); Byte((x >> 16) & 0xff); Byte((x >> 24) & 0xff);};

        Byte('R');
        Byte('I');
        Byte('F');
        Byte('F');
        Uint32(ByteSize() + 36);
        Byte('W');
        Byte('A');
        Byte('V');
        Byte('E');
        Byte('f');
        Byte('m');
        Byte('t');
        Byte(' ');
        Byte(0x10);
        Zero(3);
        Byte(0x01);
        Byte(0x00);
        Byte(Stereo() + 1);
        Byte(0x00);
        Uint32(freq);
        Uint32(FormatBytesPerSample(format) * freq);
        Byte(FormatBytesPerSample(format));
        Byte(0x00);
        Byte(Has8BitsPerSample() ? 8 : 16);
        Byte(0x00);
        Byte('d');
        Byte('a');
        Byte('t');
        Byte('a');
        Uint32(ByteSize());
        if (Has16BitsPerSample())
        {
            uint32_t samples = ByteSize() / 2;
            for (uint32_t i = 0; i < samples; i++)
            {
                const auto &ref = AtMono16(i);
                io.WriteEx(uint8_t(ref & 0xff));
                io.WriteEx(uint8_t((ref >> 8) & 0xff));
            }
        }
        else
        {
            io.WriteEx((uint8_t *)data, ByteSize());
        }
        if (ByteSize() % 2 == 1)
            Byte(0x00);
    }
    void SoundData::LoadCompressed(Utils::BinaryInput io)
    {
        Clear();

        auto ParseError = [&](const char *txt){Exception::CantParse({io.Name(), txt});};

        unsigned char tmp;

        auto CheckByte = [&](unsigned char byte, const char *error) {io.ReadEx(tmp); if (tmp != byte) ParseError(error);};

        CheckByte('~', "Magic number is missing.");
        CheckByte('^', "Magic number is missing.");
        CheckByte('\0', "Magic number is missing.");
        io.ReadEx(tmp);
        if (tmp & 0b11111100)
            ParseError("Unused bits must be set to 0.");
        switch (tmp)
        {
          case 0b00:
            format = SoundFormat::mono8;
            break;
          case 0b01:
            format = SoundFormat::stereo8;
            break;
          case 0b10:
            format = SoundFormat::mono16;
            break;
          case 0b11:
            format = SoundFormat::stereo16;
            break;
        }
        io.ReadEx(tmp); freq = tmp;
        io.ReadEx(tmp); freq |= tmp << 8;
        io.ReadEx(tmp); freq |= tmp << 16;
        io.ReadEx(tmp); freq |= tmp << 24;
        io.ReadEx(tmp); size = tmp;
        io.ReadEx(tmp); size |= tmp << 8;
        io.ReadEx(tmp); size |= tmp << 16;
        io.ReadEx(tmp); size |= tmp << 24;
        uint32_t len;
        io.ReadEx(tmp); len = tmp;
        io.ReadEx(tmp); len |= tmp << 8;
        io.ReadEx(tmp); len |= tmp << 16;
        io.ReadEx(tmp); len |= tmp << 24;
        Utils::Array<char> buf(len);
        uLongf dstlen = ByteSize();
        data.Alloc(dstlen);
        io.ReadEx((char *)buf, len);
        uncompress((unsigned char *)data, &dstlen, (unsigned char *)(char *)buf, len);

        if (Utils::big_endian && Has16BitsPerSample())
        {
            uint32_t shorts = ByteSize() / 2;
            for (uint32_t i = 0; i < shorts; i++)
                std::swap(data[i*2], data[i*2+1]);
        }
    }
    void SoundData::SaveCompressed(Utils::BinaryOutput io)
    {
        auto Byte = [&](uint8_t byte){io.WriteEx(byte);};
        auto Uint32 = [&](uint32_t byte){Byte(byte & 0xff); Byte((byte >> 8) & 0xff); Byte((byte >> 16) & 0xff); Byte((byte >> 24) & 0xff);};

        Byte('~');
        Byte('^');
        Byte('\0');
        Byte(Stereo() | (Has16BitsPerSample() << 1));
        Uint32(freq);
        Uint32(size);
        uLongf len = compressBound(ByteSize());
        Utils::Array<char> buf(len);

        if (Utils::big_endian && Stereo())
        {
            Utils::Array<unsigned char> tmpbuf(ByteSize());

            std::memcpy(tmpbuf, data, ByteSize());

            uint32_t shorts = ByteSize() / 2;

            for (uint32_t i = 0; i < shorts; i++)
                std::swap(tmpbuf[i*2], tmpbuf[i*2+1]);

            compress((unsigned char *)(char *)buf, &len, tmpbuf, ByteSize());
        }
        else
        {
            compress((unsigned char *)(char *)buf, &len, (unsigned char *)data, ByteSize());
        }
        Uint32(len);
        io.WriteEx((char *)buf, len);
    }


    void Buffer::Play(const fvec3 &pos, float volume, float pitch) const
    {
        Source src(*this);
        src.Pos(pos);
        src.Volume(volume);
        src.Pitch(pitch);
        src.Play();
    }
    void Buffer::Play(float volume, float pitch) const
    {
        Source src(*this);
        src.RelativePosition(1);
        src.Volume(volume);
        src.Pitch(pitch);
        src.Play();
    }


    void Source::Open(const Buffer &buffer)
    {
        if (id != -1)
            return;

        stereo = buffer.Stereo();
        (stereo ? stereo_manager : mono_manager).Alloc(&id);

        if (id == -1)
            return;


        auto &data = (stereo ? stereo_src_array : mono_src_array)[id];

        alGenSources(1, &data.handle);
        if (data.handle == 0)
            Sys::Error("Can't create a new audio source.");

        alSourcei(data.handle, AL_BUFFER, buffer.Handle());

        data.playing = 0;
        data.play = 0;
        data.stop = 0;
        data.full_update = 1;
        data.container_dead = 0;
        data.a.mode = SourceMode::once;
        data.a.ref_distance   = Sys::Config::openal_default_ref_distance;
        data.a.max_distance   = Sys::Config::openal_default_max_distance;
        data.a.rolloff_factor = Sys::Config::openal_default_rolloff_factor;
        data.a.volume = 1;
        data.a.pitch = 1;
        data.a.pos = {0,0,0};
        data.a.vel = {0,0,0};
        data.a.relative_position = 0;
        data.a_prev = data.a;
    }

    void Source::Close()
    {
        if (id == -1)
            return;

        auto &data = (stereo ? stereo_src_array : mono_src_array)[id];
        data.container_dead = 1;

        id = -1;
    }

    void Source::Mode(SourceMode mode)
    {
        if (id != -1)
            (stereo ? stereo_src_array : mono_src_array)[id].a.mode = mode;
    }
    void Source::RefDistance(float n)
    {
        if (id != -1)
            (stereo ? stereo_src_array : mono_src_array)[id].a.ref_distance = n;
    }
    void Source::MaxDistance(float n)
    {
        if (id != -1)
            (stereo ? stereo_src_array : mono_src_array)[id].a.max_distance = n;
    }
    void Source::RolloffPactor(float n)
    {
        if (id != -1)
            (stereo ? stereo_src_array : mono_src_array)[id].a.rolloff_factor = n;
    }
    void Source::Volume(float n)
    {
        if (id != -1)
            (stereo ? stereo_src_array : mono_src_array)[id].a.volume = n;
    }
    void Source::Pitch(float n)
    {
        if (id != -1)
            (stereo ? stereo_src_array : mono_src_array)[id].a.pitch = n;
    }
    void Source::Pos(fvec3 n)
    {
        if (id != -1)
            (stereo ? stereo_src_array : mono_src_array)[id].a.pos = n;
    }
    void Source::Vel(fvec3 n)
    {
        if (id != -1)
            (stereo ? stereo_src_array : mono_src_array)[id].a.vel = n;
    }
    void Source::RelativePosition(bool n)
    {
        if (id != -1)
            (stereo ? stereo_src_array : mono_src_array)[id].a.relative_position = n;
    }

    bool Source::Playing() const
    {
        if (id == -1)
            return 0;
        return (stereo ? stereo_src_array : mono_src_array)[id].playing;
    }

    void Source::Play()
    {
        if (id == -1)
            return;
        (stereo ? stereo_src_array : mono_src_array)[id].play = 1;
        (stereo ? stereo_src_array : mono_src_array)[id].playing = 1;
    }
    void Source::Stop()
    {
        if (id == -1)
            return;
        (stereo ? stereo_src_array : mono_src_array)[id].stop = 1;
        (stereo ? stereo_src_array : mono_src_array)[id].playing = 0;
    }

    int Source::ActiveMono()
    {
        return mono_manager.CurrentSize();
    }
    int Source::ActiveStereo()
    {
        return stereo_manager.CurrentSize();
    }
    int Source::MaxMono()
    {
        return mono_manager.MaxSize();
    }
    int Source::MaxStereo()
    {
        return stereo_manager.MaxSize();
    }
}