#pragma once

// https://wiki.osdev.org/PCI

#define PCI_CONFIG_ADDRESS  0xcf8
#define PCI_CONFIG_DATA     0xcfc

void PCICAMSelectRegister(uint8_t bus, uint8_t slot, uint8_t func, uint8_t reg) 
{ 
    uint32_t address = 
    ( ((uint32_t)1 << 31)
    | ((uint32_t)bus << 16)
    | ((uint32_t)slot << 11)
    | ((uint32_t)func << 8)
    | ((uint32_t)reg * 4)
    );
 
    outd(PCI_CONFIG_ADDRESS, address);
}

uint32_t PCICAMReadSelected32() 
{ 
    return ind(PCI_CONFIG_DATA);
}

uint32_t PCICAMRead32(uint8_t bus, uint8_t slot, uint8_t func, uint8_t reg) 
{ 
    PCICAMSelectRegister(bus, slot, func, reg);
    return ind(PCI_CONFIG_DATA);
}

void PCICheckDevice(uint8_t bus, uint8_t device, uint8_t fonction, uint8_t* functions, uint16_t* deviceId, uint16_t* vendorId, uint16_t* classCode, uint8_t* headerTypeReg, uint16_t* subVendorId, uint16_t* subDeviceId) 
{
    *deviceId = (PCICAMRead32(bus, device, fonction, 0) >> 16);
    *vendorId = (PCICAMRead32(bus, device, fonction, 0) & 0xffff);

    *classCode = (PCICAMRead32(bus, device, fonction, 2) >> 16);
 
    if((PCICAMRead32(bus, device, fonction, 0) & 0xffff) == 0xffff) 
    {
        return;
    }

    *functions = 1;

    *headerTypeReg = (PCICAMRead32(bus, device, fonction, 3) >> 16);

    uint8_t headerType = (*headerTypeReg) & 0b01111111;

    if(headerType == 2)
    {
        *subVendorId = (PCICAMRead32(bus, device, fonction, 0x10) >> 16);
        *subDeviceId = PCICAMRead32(bus, device, fonction, 0x10);
    }
    else if(headerType == 0)
    {
        *subDeviceId = (PCICAMRead32(bus, device, fonction, 0xb) >> 16);
        *subVendorId = PCICAMRead32(bus, device, fonction, 0xb);
    }
    else 
    {
        *subVendorId = 0;
        *subDeviceId = 0;
    }
}

uint16_t PCIScanBuses()
{
    uint16_t deviceCount = 0;
    for(uint16_t i = 0; i < 256; i++)
	{
		for(uint8_t j = 0; j < 32; j++)
		{
            for(uint8_t k = 0; k < 8; k++)
            {
                uint8_t func = 0, headerType = 0;
                uint16_t deviceId = 0, vendorId = 0, pciClass = 0, subVendorId = 0, subDeviceId = 0;
                PCICheckDevice(i, j, k, &func, &deviceId, &vendorId, &pciClass, &headerType, &subVendorId, &subDeviceId);
                if(deviceId != 0xffff)
                {
                    deviceCount++;
                    printf("%x:%x.%x | %x: %x:%x %x:%x\n", i, j, k, pciClass, vendorId, deviceId, subVendorId, subDeviceId);
                }
            }
		}
	}

    return deviceCount;
}