
close all;
fm = 1000;
fs = 192000;
f_max = 20000;
Ts = 1/fs;
if(fm > f_max)
    fm = f_max;
end
t = [0:Ts:1-Ts];

for i=1:1000
    sig  = sin(2*pi*i*10*t);
    sound(sig,fs);
    pause(1);
end

a = 2;
b = 5;

