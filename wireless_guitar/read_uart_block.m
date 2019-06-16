function [I,O] = read_uart_block(port,baudrate)
fclose(instrfind);
s = serial(port,'Baudrate',baudrate,'Terminator',','); % Make serial instance at specified baud rate on specified port
fopen(s);   % Open the connection
tmp1 = [];
tmp2 = [];
select = 0;
read = 0;  % Read
while(~isequal(read(1),'~'))
    read = fscanf(s);  % Read
    if(isequal(read(1),'I'))
        select = 0;    
    elseif(isequal(read(1),'O'))
        select = 1;       
    else
        if(~isequal(read(1),'~'))
            if(select == 0)
                tmp1 = [tmp1; str2double(read(1:length(read)-1))];
            else
                tmp2 = [tmp2; str2double(read(1:length(read)-1))];
            end
        end
    end
end

fclose(s);
delete(s);

I = tmp1;
O = tmp2;
end