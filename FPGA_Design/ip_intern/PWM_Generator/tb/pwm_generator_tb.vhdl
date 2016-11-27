library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity pwm_generator_tb is
end entity pwm_generator_tb;

architecture RTL of pwm_generator_tb is
	constant width : natural := 8; 
	constant freq_pwm : integer := 100_000_000;
	constant  freq_clock : integer := 10_000;
	
	signal clk : std_logic;
	signal pwmvalue : std_logic_vector(width - 1 downto 0);
	signal pwmout : std_logic;
	
begin

	clock_driver : process
		constant period : time := 10 ns;
	begin
		clk <= '0';
		wait for period / 2;
		clk <= '1';
		wait for period / 2;
	end process clock_driver;
	

	inst : entity work.pwm_generator
		generic map(
			width      => width,
			freq_clock => freq_clock,
			freq_pwm   => freq_pwm
		)
		port map(
			clk      => clk,
			pwmvalue => pwmvalue,
			pwmout   => pwmout
		);
		
	stim_proc : process is
	begin
		pwmvalue <= (others => '0');
		wait for 10 ms;
		pwmvalue <= std_logic_vector(to_unsigned(100, width));
		wait for 100 ms;
		pwmvalue <= std_logic_vector(to_unsigned(254, width));
		wait for 100 ms;
		pwmvalue <= std_logic_vector(to_unsigned(255, width));
		wait for 100 ms;
		pwmvalue <= std_logic_vector(to_unsigned(10, width));
		wait;
	end process stim_proc;
	

end architecture RTL;
