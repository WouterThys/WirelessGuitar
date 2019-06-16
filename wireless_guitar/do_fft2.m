function [four, f_max] = do_fft2(fs)
close all;

    tic;
    [input,output] = read_uart('COM7',9600);
    input=input(1:64);
    output=output(1:64);
    
    T = 1/fs;           % Sample period
    L = length(input);  % Length of signal
    L2 = length(output);
    t = (0:L-1)*T;      % Time Vector
    
    figure(1);
    subplot(2,2,1); plot(fs*t,input);   % Plot the input
    title('Input signal before');
    xlabel('time');
    
    subplot(2,2,2); plot(fs*t,output);   % Plot the input
    title('Input signal after');
    xlabel('time');
    
    NFFT = 2^nextpow2(L);   % Next power of 2 from length of input
    INPUT = fft(input,NFFT)/L;
    INPUT(1) = 0;   % Delete DC energy
    f = fs/2*linspace(0,1,NFFT/2+1);
    
    subplot(2,2,3);plot(f,2*abs(INPUT(1:NFFT/2+1)));
    title('fft');
    xlabel('Frequency (Hz)');
    ylabel('Magnitude');
    
    NFFT = 2^nextpow2(L2);   % Next power of 2 from length of input
    OUTPUT = fft(output,NFFT)/L2;
    OUTPUT(1) = 0;   % Delete DC energy
    f = fs/2*linspace(0,1,NFFT/2+1);
    
    subplot(2,2,4);plot(f,2*abs(OUTPUT(1:NFFT/2+1)));
    title('fft2');
    xlabel('Frequency (Hz)');
    ylabel('Magnitude');  

    toc;
end
