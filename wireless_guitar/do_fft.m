function [four, f_max] = do_fft1(fs)
close all;

while(1)
    tic;
    [input,output] = read_uart_block('COM7',57600);
    
    T = 1/fs;           % Sample period
    L = length(input);  % Length of signal
    L2 = length(output);
    t = (0:L-1)*T;      % Time Vector
    
    figure(1);
    subplot(2,2,1:2); plot(fs*t,input);   % Plot the input
    title('Input signal');
    xlabel('time');
    
    NFFT = 2^nextpow2(L);   % Next power of 2 from length of input
    INPUT = fft(input,NFFT)/L;
    INPUT(1) = 0;   % Delete DC energy
    f = fs/2*linspace(0,1,NFFT/2+1);
    
    [f_max_val,f_max] = max(2*abs(INPUT(1:NFFT/2+1)));
    f_max = (f_max-1)*fs/(NFFT);
    
    subplot(2,2,3);plot(f,2*abs(INPUT(1:NFFT/2+1)));
    title(['MATLAB fft, fmax: ', num2str(f_max)]);
    xlabel('Frequency (Hz)');
    ylabel('Magnitude');
    
    fpic = (0:L2-1);
    fpic = fpic*fs/NFFT;
    
    [f_max_val,f_max] = max(output);
    f_max = (f_max-1)*fs/(NFFT);

    subplot(2,2,4); plot(fpic,output);
    title(['PIC fft, fmax: ', num2str(f_max)]);
    xlabel('Frequency (Hz)');
    ylabel('Magnitude');
    
    

    toc;
end
end