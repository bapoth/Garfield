library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity rotary_encoder_tb is
end entity rotary_encoder_tb;

architecture RTL of rotary_encoder_tb is
	constant core_frequency : natural := 100_000_000;
	constant counter_width  : natural := 32;
	constant period         : time    := 10 ns;

	signal clk                   : std_logic;
	signal rst                   : std_logic;
	signal clear_counter, enable : std_logic;
	signal counter               : std_logic_vector(counter_width - 1 downto 0);
	signal rotary_signal         : std_logic;
	signal counter_error         : boolean;

	signal counter_int : integer range 0 to integer'high := 0;

begin
	rot_inst : entity work.rotary_encoder
		generic map(
			core_frequency => core_frequency,
			counter_width  => counter_width
		)
		port map(
			clk           => clk,
			rst           => rst,
			clear_counter => clear_counter,
			enable        => enable,
			counter       => counter,
			counter_error => counter_error,
			rotary_signal => rotary_signal
		);

	counter_int <= to_integer(unsigned(counter));

	clock_driver : process
	begin
		clk <= '0';
		wait for period / 2;
		clk <= '1';
		wait for period / 2;
	end process clock_driver;

	rotary_signal_stim : process is
	begin
		rotary_signal <= '0';
		wait for 1 ms;
		for i in 0 to 25 loop
			rotary_signal <= '1';
			wait for 1 ms;
			rotary_signal <= '0';
			wait for 1 ms;
		end loop;
		report "End of the first for loop, the counter value is " & integer'image(counter_int) severity note;
		if counter_int /= 26 then
			report "The countervalue does not match the right value, the value is " & integer'image(counter_int) severity error;

		end if;

		for i in 0 to 10 loop
			rotary_signal <= '1';
			wait for 8 ms;
			rotary_signal <= '0';
			wait for 8 ms;
		end loop;
	end process rotary_signal_stim;

	stim_proc : process is
	begin
		rst           <= '1';
		clear_counter <= '0';
		wait for 100 ns;
		rst           <= '0';
		enable        <= '1';
		wait for 75 ms;
		clear_counter <= '1';
		wait for period;
		clear_counter <= '0';
		wait;
	end process stim_proc;

end architecture RTL;
