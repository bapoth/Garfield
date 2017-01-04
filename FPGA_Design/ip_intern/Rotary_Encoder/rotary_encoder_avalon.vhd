library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity rotary_encoder_avalon is
	generic(
		datawidth : natural := 32
	);
	port(
		-- ! avalon clk interface
		clk                     : in  std_logic;
		-- ! avalon reset interface
		rst                     : in  std_logic;
		-- ! avalon MM interface
		address                 : in  std_logic_vector(0 downto 0);
		read, write, chipselect : in  std_logic;
		writedata               : in  std_logic_vector(datawidth - 1 downto 0);
		readdata                : out std_logic_vector(datawidth - 1 downto 0);
		waitrequest             : out std_logic;
		-- ! avalon input interface
		rotary_signal           : in  std_logic
	);
end entity rotary_encoder_avalon;

architecture RTL of rotary_encoder_avalon is
	-- --------------------------------------
	-- constants
	-- --------------------------------------
	constant bit_enable_pos       : natural := 0;
	constant bit_clearcounter_pos : natural := 1;
	constant bit_resetcore_pos    : natural := 2;
	constant bit_countererror_pos : natural := 16;

	-- --------------------------------------
	-- signals
	-- --------------------------------------
	signal datavalid_write : boolean := false;
	signal reset_int       : std_logic;

	signal clear_counter : std_logic;
	signal enable        : std_logic;
	signal counter       : std_logic_vector(datawidth - 1 downto 0);
	signal counter_error : boolean;

	-- --------------------------------------
	-- signals as registers
	-- --------------------------------------
	signal control_register_path : std_logic_vector(datawidth/2 - 1 downto 0) := (others => '0');
	signal status_register_path  : std_logic_vector(datawidth/2 - 1 downto 0) := (others => '0');

	signal control_status_register : std_logic_vector(datawidth - 1 downto 0);
	-- --------------------------------------
	-- components
	-- --------------------------------------
	component rotary_encoder
		generic(
			core_frequency : natural := 100_000_000;
			counter_width  : natural := 32
		);
		port(
			clk           : in  std_logic;
			rst           : in  std_logic;
			clear_counter : in  std_logic;
			enable        : in  std_logic;
			counter       : out std_logic_vector(counter_width - 1 downto 0);
			counter_error : out boolean;
			rotary_signal : in  std_logic
		);
	end component rotary_encoder;

begin
	-- --------------------------------------
	-- components instantiations
	-- --------------------------------------

	rotary_enc_inst : rotary_encoder
		generic map(
			core_frequency => 100_000_000,
			counter_width  => datawidth
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

	-- --------------------------------------
	-- concurrent statements
	-- --------------------------------------
	control_status_register <= status_register_path & control_register_path;

	reset_int                                                <= rst or control_register_path(bit_resetcore_pos);
	waitrequest                                              <= '1' when (write = '1' and chipselect = '1') and not datavalid_write else '0';
	status_register_path(bit_countererror_pos - datawidth/2) <= '1' when counter_error else '0';

	enable        <= control_register_path(bit_enable_pos);
	clear_counter <= control_register_path(bit_clearcounter_pos);

	-- --------------------------------------
	-- processes
	-- --------------------------------------
	write_proc : process(clk) is
	begin
		if rising_edge(clk) then
			control_register_path(bit_clearcounter_pos) <= '0';
			datavalid_write <= false;
			if reset_int = '1' then
				control_register_path <= (others => '0');
			elsif chipselect = '1' and write = '1' then
				case address is
					when "0" =>         -- the control register; base address 0x00
						control_register_path(bit_enable_pos)       <= writedata(bit_enable_pos);
						control_register_path(bit_clearcounter_pos) <= writedata(bit_clearcounter_pos);
						control_register_path(bit_resetcore_pos)    <= writedata(bit_resetcore_pos);
					when "1" =>         -- the result register, there is no write allowed; base address 0x04
						null;
					when others =>
						null;
				end case;
				datavalid_write <= true;
			else
				null;
			end if;
		end if;
	end process write_proc;

	read_proc : process(address, chipselect, control_status_register, counter, read) is
	begin
		readdata <= (others => '0');
		if chipselect = '1' and read = '1' then
			case address is
				when "0" =>             -- control/status register
					readdata <= control_status_register;
				when "1" =>             -- result register
					readdata <= counter;
				when others => null;
			end case;
		end if;
	end process read_proc;

end architecture RTL;
