################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
lazy-blinker.lss \

FLASH_IMAGE += \
lazy-blinker.hex \

EEPROM_IMAGE += \
lazy-blinker.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: lazy-blinker.elf secondary-outputs

# Tool invocations
lazy-blinker.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,lazy-blinker.map -mmcu=attiny13 -o "lazy-blinker.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

lazy-blinker.lss: lazy-blinker.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S lazy-blinker.elf  >"lazy-blinker.lss"
	@echo 'Finished building: $@'
	@echo ' '

lazy-blinker.hex: lazy-blinker.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex lazy-blinker.elf  "lazy-blinker.hex"
	@echo 'Finished building: $@'
	@echo ' '

lazy-blinker.eep: lazy-blinker.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex lazy-blinker.elf  "lazy-blinker.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: lazy-blinker.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny13 lazy-blinker.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) lazy-blinker.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
