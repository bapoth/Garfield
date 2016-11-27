-- inspired from Lothar Millers example on his homepage

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity pwm_generator is
	Generic(width      : natural := 8;  -- Breite
		    freq_clock : integer := 50000000; -- Taktfrequenz
		    freq_pwm   : integer := 1000 -- PWM-Frequenz
	);
	Port(clk      : in  std_logic;
		 pwmvalue : in  std_logic_vector(width - 1 downto 0);
		 pwmout   : out std_logic
	);
end pwm_generator;

architecture RTL of pwm_generator is
	signal cnt : integer range 0 to 2 ** width - 2                             := 0;
	signal pre : integer range 0 to freq_clock / (freq_pwm * (2 ** width - 2)) := 0;
begin
	-- prescaler
	process
	begin
		wait until rising_edge(clk);
		if (pre < freq_clock / (freq_pwm * (2 ** width))) then
			pre <= pre + 1;
		else
			pre <= 0;
		end if;
	end process;

	-- pwm counter       
	process
	begin
		wait until rising_edge(clk);
		if (pre = 0) then
			if (cnt < 2 ** width - 2) then
				cnt <= cnt + 1;
			else
				cnt <= 0;
			end if;
		end if;
	end process;

	-- output without glitches
	process
	begin
		wait until rising_edge(clk);
		if (cnt >= to_integer(unsigned(pwmvalue))) then
			pwmout <= '0';
		else
			pwmout <= '1';
		end if;
	end process;
end RTL;



