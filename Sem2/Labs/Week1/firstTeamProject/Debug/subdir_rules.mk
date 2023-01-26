################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
CCS6_Intro_main.obj: ../CCS6_Intro_main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --define=c6748 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="CCS6_Intro_main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

block_sine.obj: ../block_sine.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --define=c6748 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="block_sine.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


