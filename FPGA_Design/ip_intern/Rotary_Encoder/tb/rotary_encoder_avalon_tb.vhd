library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity rotary_encoder_avalon_tb is
end entity rotary_encoder_avalon_tb;

architecture RTL of rotary_encoder_avalon_tb is

	constant datawidth : natural := 32;
	constant period    : time    := 10 ns; -- 100 Mhz

	signal clk           : std_logic;
	signal rst           : std_logic;
	signal address       : std_logic_vector(0 downto 0)             := (others => '0');
	signal read          : std_logic                                := '0';
	signal write         : std_logic                                := '0';
	signal chipselect    : std_logic                                := '0';
	signal writedata     : std_logic_vector(datawidth - 1 downto 0) := (others => '0');
	signal readdata      : std_logic_vector(datawidth - 1 downto 0);
	signal waitrequest   : std_logic;
	signal rotary_signal : std_logic                                := '0';

begin

	clock_driver : process
	begin
		clk <= '0';
		wait for period / 2;
		clk <= '1';
		wait for period / 2;
	end process clock_driver;

	rotary_signal_proc : process
	begin
		rotary_signal <= '0';
		wait for 1 ms;
		rotary_signal <= '1';
		wait for 1 ms;
	end process rotary_signal_proc;

	av_rot_inst : entity work.rotary_encoder_avalon
		generic map(
			datawidth => datawidth
		)
		port map(
			clk           => clk,
			rst           => rst,
			address       => address,
			read          => read,
			write         => write,
			chipselect    => chipselect,
			writedata     => writedata,
			readdata      => readdata,
			waitrequest   => waitrequest,
			rotary_signal => rotary_signal
		);

	stim_proc : process is
	begin
		rst        <= '1';
		wait until rising_edge(clk);
		rst        <= '0';
		address    <= (others => '0');
		write      <= '1';
		chipselect <= '1';
		writedata  <= x"00000001";
		wait until falling_edge(waitrequest);
		chipselect <= '0';
		write      <= '0';
		wait for 30 ms;
		wait until rising_edge(clk);
		chipselect <= '1';
		read       <= '1';
		address    <= "1";
		wait until rising_edge(clk);
		chipselect <= '0';
		read       <= '0';
		wait until rising_edge(clk);
		address    <= "0";
		chipselect <= '1';
		write      <= '1';
		writedata  <= x"00000003";
		wait until falling_edge(waitrequest);
		chipselect <= '0';
		wait;
	end process stim_proc;

end architecture RTL;
