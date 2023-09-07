#pragma once

#include <ata.h>
#include <scsi.h>
#include <classpnp.h>

#include <ntddscsi.h>
#include <ntdddisk.h>
#include <ntddndis.h>

#include <mountdev.h>
#include <mountmgr.h>

extern BOOLEAN SpoofEnabl;

auto RestartWmiPrvSE()->NTSTATUS;

auto SpoofReg()->NTSTATUS;

auto SpoofHdd()->NTSTATUS;

auto SpoofNic()->NTSTATUS;

auto SpoofFile()->NTSTATUS;

auto SpoofNdis()->NTSTATUS;

auto SpoofNsiEx()->NTSTATUS;

auto SpoofGpuEx()->NTSTATUS;

auto SpoofPartEx()->NTSTATUS;

auto SpoofDiskEx()->NTSTATUS;

auto SpoofSmbios()->NTSTATUS;

auto SpoofVolumes()->NTSTATUS;

auto SpoofVolumesEx()->NTSTATUS;

auto SpoofInitialize(ULONG)->NTSTATUS;
