--! @file

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity rotary_encoder is
	generic(
		--! the nominal frequency of the clock
		core_frequency : natural := 100_000_000;
		--! the width of the outputed counter register
		counter_width  : natural := 32
	);
	port(
		--! the clk from the core
		clk           : in  std_logic;
		--! general reset from the core
		rst           : in  std_logic;

		--! for clearing the internal counter, this signal must be HIGH
		--! it only counts rising edges on the signal line!
		clear_counter : in  std_logic;
		--! enable signal, if low, the counter will not count anymore
		enable        : in  std_logic;
		--! the counter register which contains counts since the last clear_counter or rst
		counter       : out std_logic_vector(counter_width - 1 downto 0);
		--! shows if there was an error with the counting; if there was an error, the counter starts from zero
		counter_error : out boolean;
		--! the signal from outside the fpga system which comes from a led or rotary sensor
		rotary_signal : in  std_logic
	);
end entity rotary_encoder;

architecture RTL of rotary_encoder is
	signal old_signal : bit := '0';

	signal internal_counter       : unsigned(counter_width - 1 downto 0) := (others => '0');
	
	signal reset_counter : boolean := false;

begin
	
	reset_counter <= true when rst = '1' or clear_counter = '1' else false;
	counter <= std_logic_vector(internal_counter);
	
	signal_counting : process(clk) is
	begin
		if rising_edge(clk) then
			if reset_counter = true then
				internal_counter <= (others => '0');
			else
				if enable = '1' then
					old_signal <= '0';
					if rotary_signal = '0' and old_signal = '0' then
						-- nothing changed
						old_signal <= '0';
					elsif rotary_signal = '0' and old_signal = '1' then
						-- falling edge
						old_signal <= '0';
					elsif rotary_signal = '1' and old_signal = '0' then
						-- now there was a rising edge on the rotary_signal
						old_signal       <= '1';
						internal_counter <= internal_counter + 1;
					elsif rotary_signal = '1' and old_signal = '1' then
						-- there was and is high level
						old_signal <= '1';
					else
						counter_error    <= true;
						internal_counter <= (others => '0');
					end if;
				end if;
			end if;
		end if;
	end process signal_counting;

end architecture RTL;
