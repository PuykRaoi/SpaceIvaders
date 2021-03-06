#include "io_devices.h"
#include <iostream>
#include <fstream>


void Io_devices::Initialize()
{
    port1 = 0x00;
    portout3 = 0x00;
    portout5 = 0x00;

    shift_register_value = 0x0000;

    lastShootSoundActive     = false;
    lastExplosionSoundActive = false;
    lastInvaderkilledSound   = false;
    lastFastinvader1Sound    = false;
    lastFastinvader2Sound    = false;
    lastFastinvader3Sound    = false;
    lastFastinvader4Sound    = false;
    lastUforepeatSound       = false;
}

void Io_devices::Connect(PLATFORMTYPE* platform)
{
    m_platform = platform;
}

uint8_t Io_devices::Read_device(uint8_t device_number)
{
    switch(device_number)
    {
        case 0x1: return port1; break;
        case 0x3: return Get_shift_register_result(); break;
        default : return 0u;
    }
}

void Io_devices::Write_device(uint8_t device_number, uint8_t data)
{
    switch(device_number)
    {
        case 0x2: Set_shift_register_result_offset(data);   break;
        case 0x3: portout3 = data;                          break;
        case 0x5: portout5 = data;                          break;
        case 0x4: Fill_shift_register(data);                break;
        default : break;
    }
}

uint8_t Io_devices::Get_shift_register_result()
{
    return
        ((shift_register_value >> (8-shift_register_offset)) & 0xff);
}

void Io_devices::Set_shift_register_result_offset(uint8_t amount)
{
    shift_register_offset = amount & 0x7;
}

void Io_devices::Fill_shift_register(uint8_t data)
{
    shift_register_value =
        (shift_register_value >> 8) |
        (data << 8);
}

void Io_devices::UpdateSounds()
{
    currentUforepeatSound       = ((portout3 & 0x01) != 0);
    currentShootSoundActive     = ((portout3 & 0x02) != 0);
    currentExplosionSoundActive = ((portout3 & 0x04) != 0);
    currentInvaderkilledSound   = ((portout3 & 0x08) != 0);
    currentFastinvader1Sound    = ((portout5 & 0x01) != 0);
    currentFastinvader2Sound    = ((portout5 & 0x02) != 0);
    currentFastinvader3Sound    = ((portout5 & 0x04) != 0);
    currentFastinvader4Sound    = ((portout5 & 0x08) != 0);
    currentUfohitSound          = ((portout5 & 0x10) != 0);
    if (!lastShootSoundActive && currentShootSoundActive) { m_platform->PlaySound(SNDID_SHOOT); }
    if (lastShootSoundActive && !currentShootSoundActive) { m_platform->StopSound(SNDID_SHOOT); }
    lastShootSoundActive = currentShootSoundActive;

    if (!lastExplosionSoundActive && currentExplosionSoundActive) { m_platform->PlaySound(SNDID_EXPLOSION); }
    if (lastExplosionSoundActive && !currentExplosionSoundActive) { m_platform->StopSound(SNDID_EXPLOSION); }
    lastExplosionSoundActive = currentExplosionSoundActive;

    if (!lastInvaderkilledSound && currentInvaderkilledSound) { m_platform->PlaySound(SNDID_INVKLLD); }
    if (lastInvaderkilledSound && !currentInvaderkilledSound) { m_platform->StopSound(SNDID_INVKLLD); }
    lastInvaderkilledSound = currentInvaderkilledSound;

    if (!lastFastinvader1Sound && currentFastinvader1Sound) { m_platform->PlaySound(SNDID_FSTINV1); }
    if (lastFastinvader1Sound && !currentFastinvader1Sound) { m_platform->StopSound(SNDID_FSTINV1); }
    lastFastinvader1Sound = currentFastinvader1Sound;

    if (!lastFastinvader2Sound && currentFastinvader2Sound) { m_platform->PlaySound(SNDID_FSTINV2); }
    if (lastFastinvader2Sound && !currentFastinvader2Sound) { m_platform->StopSound(SNDID_FSTINV2); }
    lastFastinvader2Sound = currentFastinvader2Sound;

    if (!lastFastinvader3Sound && currentFastinvader3Sound) { m_platform->PlaySound(SNDID_FSTINV3); }
    if (lastFastinvader3Sound && !currentFastinvader3Sound) { m_platform->StopSound(SNDID_FSTINV3); }
    lastFastinvader3Sound = currentFastinvader3Sound;

    if (!lastFastinvader4Sound && currentFastinvader4Sound) { m_platform->PlaySound(SNDID_FSTINV4); }
    if (lastFastinvader4Sound && !currentFastinvader4Sound) { m_platform->StopSound(SNDID_FSTINV4); }
    lastFastinvader4Sound = currentFastinvader4Sound;

    if (!lastUforepeatSound && currentUforepeatSound) { m_platform->PlaySound(SNDID_UFOREPT); }
    if (lastUforepeatSound && !currentUforepeatSound) { m_platform->StopSound(SNDID_UFOREPT); }
    lastUforepeatSound = currentUforepeatSound;

    if (!lastUfohitSound && currentUfohitSound) { m_platform->PlaySound(SNDID_UFOHIT); }
    if (lastUfohitSound && !currentUfohitSound) { m_platform->StopSound(SNDID_UFOHIT); }
    lastUfohitSound = currentUfohitSound;
}

