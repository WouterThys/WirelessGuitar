function [a,b] = uart_read_byte(port, baudrate)
read = zeros(1,100);
stop = 0;
k=[];
set(gcf,'keypress','k=get(gcf,''currentchar'');');
    s = serial(port,'Baudrate',baudrate,'Terminator',','); % Make serial instance at specified baud rate on specified port
    fopen(s);   % Open the connection
    while(~stop)
        read = [read fscanf(s)];  % Read
        read = read(2:end);
        plot(read);
        Hold on;
        
         if ~isempty(k)
            if strcmp(k,'s'); break; end;
            if strcmp(k,'p'); pause; k=[]; end;
        end
    end
    
    fclose(s);
delete(s);
end