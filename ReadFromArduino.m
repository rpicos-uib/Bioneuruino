function ReadFromArduinoOriginal(tplot)
    close all;
    clc;
    value = 0;
    
    t(1) = 0;   %Comptador temporal eix 'x'
    t0 = 0;
    dt = 0.05; %Pas d'integració al RK45 de Arduino
    tfin = tplot; %temps final de la mostra
    
    samples = tfin/dt;

    delete(instrfind({'port'},{'COM6'}));
    port = serialport('COM6',2000000);
    
    %fopen(puerto);
    count = 1;

    figure('Name','Potencial de membrana')
    %title('Potencial de membrana');
    xlabel('Time(ms)');
    ylabel('Vm(mV)');
    grid off;
    hold on;

    while count <= samples
        ylim([-100 70]);
        xlim([0 tfin]);
        StringValue = (readline(port));
        StringValueReal = str2double(StringValue);
        value(count) = StringValueReal(1);
        plot(t,value);
        count = count + 1;
        t0 = t0 + dt;
        t(count) = t0;
    end
    delete(port);
    clear all;
end
