library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity pwm_generator_avalon is
	generic(
		datawidth : natural := 32;
		freq_core : natural := 100_000_000;
		freq_pwm  : natural := 10_000
	);
	port(
		-- avalon clk interface, there is no need for a reset
		clk                     : in  std_logic;
		reset                   : in  std_logic;
		-- avalon MM interface
		address                 : in  std_logic_vector(0 downto 0);
		read, write, chipselect : in  std_logic;
		writedata               : in  std_logic_vector(datawidth - 1 downto 0);
		readdata                : out std_logic_vector(datawidth - 1 downto 0);
		waitrequest             : out std_logic;
		-- avalon output interface
		pwm_output_signal       : out std_logic
	);
end entity pwm_generator_avalon;

architecture RTL of pwm_generator_avalon is

	----------------------------------------
	-- constants
	----------------------------------------
    constant pwm_generator_bit_width : natural := 8;

	----------------------------------------
	-- signals
	----------------------------------------
	signal datavalid_write : boolean := false;

	----------------------------------------
	-- signals as registers
	----------------------------------------
	signal control_register : std_logic_vector(datawidth - 1 downto 0);

	----------------------------------------
	-- components
	----------------------------------------
	component pwm_generator
		generic(
			width      : natural := 8;
			freq_clock : integer := 50000000;
			freq_pwm   : integer := 1000
		);
		port(
			clk      : in  std_logic;
			pwmvalue : in  std_logic_vector(width - 1 downto 0);
			pwmout   : out std_logic
		);
	end component pwm_generator;
begin

	----------------------------------------
	-- component instantiations
	----------------------------------------
	pwm_gen_inst : pwm_generator
		generic map(
			width      => pwm_generator_bit_width,
			freq_clock => freq_core,
			freq_pwm   => freq_pwm
		)
		port map(
			clk      => clk,
			pwmvalue(pwm_generator_bit_width -1 downto 0) => control_register(pwm_generator_bit_width - 1 downto 0),
			pwmout   => pwm_output_signal
		);

	----------------------------------------
	-- concurrent statements
	----------------------------------------
	waitrequest <= '1' when (write = '1' and chipselect = '1') and not datavalid_write else '0'; -- waitrequest must be asynchron and high until the data are taken

	----------------------------------------
	-- processes
	----------------------------------------

    --! @brief
	write_proc : process(clk) is
	begin
		if rising_edge(clk) then
            datavalid_write <= false;
			if reset = '1' then
				control_register <= (others => '0');
			elsif chipselect = '1' then
                if write = '1' then
    				case (address) is
    					when "0" =>
    						control_register(pwm_generator_bit_width - 1 downto 0) <= writedata(pwm_generator_bit_width - 1 downto 0);
                        when others =>
                            null;
    				end case;
    				datavalid_write <= true;
                end if;
			end if;
		end if;
	end process write_proc;

	--! @brief
	read_proc : process(chipselect, read, address, control_register) is
	begin
		if chipselect = '1' and read = '1' then
			case address is
				when "0" =>
					readdata <= control_register;
				when others =>
					null;
			end case;

		end if;
	end process read_proc;

end architecture RTL;
