
set DEBUG=/Od /Zi
set FXC_VS=fxc /T vs_5_0 /E vs_main
set FXC_PS=fxc /T ps_5_0 /E ps_main

%FXC_VS% %DEBUG% /Fo shader_vs_d.so shaders.hlsl
%FXC_VS% /Fo shader_vs.so shaders.hlsl

%FXC_PS% %DEBUG% /Fo shader_ps_d.so shaders.hlsl
%FXC_PS% /Fo shader_ps.so shaders.hlsl

