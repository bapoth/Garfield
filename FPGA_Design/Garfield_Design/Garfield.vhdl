library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Garfield is
	port(
		ADC_CONVST       : out   std_logic;
		ADC_SCK          : out   std_logic;
		ADC_SDI          : out   std_logic;
		ADC_SDO          : in    std_logic;
		-- ARDUINO
		ARDUINO_IO       : inout std_logic_vector(15 downto 0);
		ARDUINO_RESET_N  : inout std_logic;
		-- CLK
		-- CLK_I2C_SCL : out std_logic;
		-- CLK_I2C_SDA : inout std_logic;

		-- FPGA
		FPGA_CLK1_50     : in    std_logic;
		FPGA_CLK2_50     : in    std_logic;
		FPGA_CLK3_50     : in    std_logic;
		-- GPIO
		GPIO_0           : inout std_logic_vector(35 downto 0);
		GPIO_1           : inout std_logic_vector(35 downto 0);
		-- HPS
		HPS_CONV_USB_N   : inout std_logic;
		HPS_DDR3_ADDR    : out   std_logic_vector(14 downto 0);
		HPS_DDR3_BA      : out   std_logic_vector(2 downto 0);
		HPS_DDR3_CAS_N   : out   std_logic;
		HPS_DDR3_CKE     : out   std_logic;
		HPS_DDR3_CK_N    : out   std_logic;
		HPS_DDR3_CK_P    : out   std_logic;
		HPS_DDR3_CS_N    : out   std_logic;
		HPS_DDR3_DM      : out   std_logic_vector(3 downto 0);
		HPS_DDR3_DQ      : inout std_logic_vector(31 downto 0);
		HPS_DDR3_DQS_N   : inout std_logic_vector(3 downto 0);
		HPS_DDR3_DQS_P   : inout std_logic_vector(3 downto 0);
		HPS_DDR3_ODT     : out   std_logic;
		HPS_DDR3_RAS_N   : out   std_logic;
		HPS_DDR3_RESET_N : out   std_logic;
		HPS_DDR3_RZQ     : in    std_logic;
		HPS_DDR3_WE_N    : out   std_logic;
		HPS_ENET_GTX_CLK : out   std_logic;
		HPS_ENET_INT_N   : inout std_logic;
		HPS_ENET_MDC     : out   std_logic;
		HPS_ENET_MDIO    : inout std_logic;
		HPS_ENET_RX_CLK  : in    std_logic;
		HPS_ENET_RX_DATA : in    std_logic_vector(3 downto 0);
		HPS_ENET_RX_DV   : in    std_logic;
		HPS_ENET_TX_DATA : out   std_logic_vector(3 downto 0);
		HPS_ENET_TX_EN   : out   std_logic;
		HPS_GSENSOR_INT  : inout std_logic;
		HPS_I2C0_SCLK    : inout std_logic;
		HPS_I2C0_SDAT    : inout std_logic;
		HPS_I2C1_SCLK    : inout std_logic;
		HPS_I2C1_SDAT    : inout std_logic;
		HPS_KEY          : inout std_logic;
		HPS_LED          : inout std_logic;
		HPS_LTC_GPIO     : inout std_logic;
		HPS_SD_CLK       : out   std_logic;
		HPS_SD_CMD       : inout std_logic;
		HPS_SD_DATA      : inout std_logic_vector(3 downto 0);
		HPS_SPIM_CLK     : out   std_logic;
		HPS_SPIM_MISO    : in    std_logic;
		HPS_SPIM_MOSI    : out   std_logic;
		HPS_SPIM_SS      : inout std_logic;
		HPS_UART_RX      : in    std_logic;
		HPS_UART_TX      : out   std_logic;
		HPS_USB_CLKOUT   : in    std_logic;
		HPS_USB_DATA     : inout std_logic_vector(7 downto 0);
		HPS_USB_DIR      : in    std_logic;
		HPS_USB_NXT      : in    std_logic;
		HPS_USB_STP      : out   std_logic;
		-- Key
		KEY              : in    std_logic_vector(1 downto 0);
		-- LEDs
		LED              : out   std_logic_vector(7 downto 0);
		-- SW
		SW               : in    std_logic_vector(3 downto 0)
	);
end Garfield;

architecture RTL of Garfield is

    component Garfield_system is
		port (
			clk_clk                                          : in    std_logic                     := 'X';             -- clk
			clk_1_fpga_clock_clk                             : in    std_logic                     := 'X';             -- clk
			clk_1_fpga_reset_reset_n                         : in    std_logic                     := 'X';             -- reset_n
			drive_pwm_pwm_signal_export                      : out   std_logic;                                        -- export
			garfield_general_io_external_connection_export   : out   std_logic_vector(7 downto 0);                     -- export
			garfield_lighting_led_external_connection_export : out   std_logic_vector(3 downto 0);                     -- export
			hps_0_f2h_cold_reset_req_reset_n                 : in    std_logic                     := 'X';             -- reset_n
			hps_0_f2h_debug_reset_req_reset_n                : in    std_logic                     := 'X';             -- reset_n
			hps_0_f2h_stm_hw_events_stm_hwevents             : in    std_logic_vector(27 downto 0) := (others => 'X'); -- stm_hwevents
			hps_0_f2h_warm_reset_req_reset_n                 : in    std_logic                     := 'X';             -- reset_n
			hps_0_h2f_reset_reset_n                          : out   std_logic;                                        -- reset_n
			hps_0_hps_io_hps_io_emac1_inst_TX_CLK            : out   std_logic;                                        -- hps_io_emac1_inst_TX_CLK
			hps_0_hps_io_hps_io_emac1_inst_TXD0              : out   std_logic;                                        -- hps_io_emac1_inst_TXD0
			hps_0_hps_io_hps_io_emac1_inst_TXD1              : out   std_logic;                                        -- hps_io_emac1_inst_TXD1
			hps_0_hps_io_hps_io_emac1_inst_TXD2              : out   std_logic;                                        -- hps_io_emac1_inst_TXD2
			hps_0_hps_io_hps_io_emac1_inst_TXD3              : out   std_logic;                                        -- hps_io_emac1_inst_TXD3
			hps_0_hps_io_hps_io_emac1_inst_RXD0              : in    std_logic                     := 'X';             -- hps_io_emac1_inst_RXD0
			hps_0_hps_io_hps_io_emac1_inst_MDIO              : inout std_logic                     := 'X';             -- hps_io_emac1_inst_MDIO
			hps_0_hps_io_hps_io_emac1_inst_MDC               : out   std_logic;                                        -- hps_io_emac1_inst_MDC
			hps_0_hps_io_hps_io_emac1_inst_RX_CTL            : in    std_logic                     := 'X';             -- hps_io_emac1_inst_RX_CTL
			hps_0_hps_io_hps_io_emac1_inst_TX_CTL            : out   std_logic;                                        -- hps_io_emac1_inst_TX_CTL
			hps_0_hps_io_hps_io_emac1_inst_RX_CLK            : in    std_logic                     := 'X';             -- hps_io_emac1_inst_RX_CLK
			hps_0_hps_io_hps_io_emac1_inst_RXD1              : in    std_logic                     := 'X';             -- hps_io_emac1_inst_RXD1
			hps_0_hps_io_hps_io_emac1_inst_RXD2              : in    std_logic                     := 'X';             -- hps_io_emac1_inst_RXD2
			hps_0_hps_io_hps_io_emac1_inst_RXD3              : in    std_logic                     := 'X';             -- hps_io_emac1_inst_RXD3
			hps_0_hps_io_hps_io_sdio_inst_CMD                : inout std_logic                     := 'X';             -- hps_io_sdio_inst_CMD
			hps_0_hps_io_hps_io_sdio_inst_D0                 : inout std_logic                     := 'X';             -- hps_io_sdio_inst_D0
			hps_0_hps_io_hps_io_sdio_inst_D1                 : inout std_logic                     := 'X';             -- hps_io_sdio_inst_D1
			hps_0_hps_io_hps_io_sdio_inst_CLK                : out   std_logic;                                        -- hps_io_sdio_inst_CLK
			hps_0_hps_io_hps_io_sdio_inst_D2                 : inout std_logic                     := 'X';             -- hps_io_sdio_inst_D2
			hps_0_hps_io_hps_io_sdio_inst_D3                 : inout std_logic                     := 'X';             -- hps_io_sdio_inst_D3
			hps_0_hps_io_hps_io_usb1_inst_D0                 : inout std_logic                     := 'X';             -- hps_io_usb1_inst_D0
			hps_0_hps_io_hps_io_usb1_inst_D1                 : inout std_logic                     := 'X';             -- hps_io_usb1_inst_D1
			hps_0_hps_io_hps_io_usb1_inst_D2                 : inout std_logic                     := 'X';             -- hps_io_usb1_inst_D2
			hps_0_hps_io_hps_io_usb1_inst_D3                 : inout std_logic                     := 'X';             -- hps_io_usb1_inst_D3
			hps_0_hps_io_hps_io_usb1_inst_D4                 : inout std_logic                     := 'X';             -- hps_io_usb1_inst_D4
			hps_0_hps_io_hps_io_usb1_inst_D5                 : inout std_logic                     := 'X';             -- hps_io_usb1_inst_D5
			hps_0_hps_io_hps_io_usb1_inst_D6                 : inout std_logic                     := 'X';             -- hps_io_usb1_inst_D6
			hps_0_hps_io_hps_io_usb1_inst_D7                 : inout std_logic                     := 'X';             -- hps_io_usb1_inst_D7
			hps_0_hps_io_hps_io_usb1_inst_CLK                : in    std_logic                     := 'X';             -- hps_io_usb1_inst_CLK
			hps_0_hps_io_hps_io_usb1_inst_STP                : out   std_logic;                                        -- hps_io_usb1_inst_STP
			hps_0_hps_io_hps_io_usb1_inst_DIR                : in    std_logic                     := 'X';             -- hps_io_usb1_inst_DIR
			hps_0_hps_io_hps_io_usb1_inst_NXT                : in    std_logic                     := 'X';             -- hps_io_usb1_inst_NXT
			hps_0_hps_io_hps_io_spim1_inst_CLK               : out   std_logic;                                        -- hps_io_spim1_inst_CLK
			hps_0_hps_io_hps_io_spim1_inst_MOSI              : out   std_logic;                                        -- hps_io_spim1_inst_MOSI
			hps_0_hps_io_hps_io_spim1_inst_MISO              : in    std_logic                     := 'X';             -- hps_io_spim1_inst_MISO
			hps_0_hps_io_hps_io_spim1_inst_SS0               : out   std_logic;                                        -- hps_io_spim1_inst_SS0
			hps_0_hps_io_hps_io_uart0_inst_RX                : in    std_logic                     := 'X';             -- hps_io_uart0_inst_RX
			hps_0_hps_io_hps_io_uart0_inst_TX                : out   std_logic;                                        -- hps_io_uart0_inst_TX
			hps_0_hps_io_hps_io_i2c0_inst_SDA                : inout std_logic                     := 'X';             -- hps_io_i2c0_inst_SDA
			hps_0_hps_io_hps_io_i2c0_inst_SCL                : inout std_logic                     := 'X';             -- hps_io_i2c0_inst_SCL
			hps_0_hps_io_hps_io_i2c1_inst_SDA                : inout std_logic                     := 'X';             -- hps_io_i2c1_inst_SDA
			hps_0_hps_io_hps_io_i2c1_inst_SCL                : inout std_logic                     := 'X';             -- hps_io_i2c1_inst_SCL
			hps_0_hps_io_hps_io_gpio_inst_GPIO09             : inout std_logic                     := 'X';             -- hps_io_gpio_inst_GPIO09
			hps_0_hps_io_hps_io_gpio_inst_GPIO35             : inout std_logic                     := 'X';             -- hps_io_gpio_inst_GPIO35
			hps_0_hps_io_hps_io_gpio_inst_GPIO40             : inout std_logic                     := 'X';             -- hps_io_gpio_inst_GPIO40
			hps_0_hps_io_hps_io_gpio_inst_GPIO53             : inout std_logic                     := 'X';             -- hps_io_gpio_inst_GPIO53
			hps_0_hps_io_hps_io_gpio_inst_GPIO54             : inout std_logic                     := 'X';             -- hps_io_gpio_inst_GPIO54
			hps_0_hps_io_hps_io_gpio_inst_GPIO61             : inout std_logic                     := 'X';             -- hps_io_gpio_inst_GPIO61
			i2c_opencores_0_export_sda_pad_in                : in    std_logic                     := 'X';             -- sda_pad_in
			i2c_opencores_0_export_sda_pad_out               : out   std_logic;                                        -- sda_pad_out
			i2c_opencores_0_export_sda_pad_en                : out   std_logic;                                        -- sda_pad_en
			i2c_opencores_0_export_scl_pad_in                : in    std_logic                     := 'X';             -- scl_pad_in
			i2c_opencores_0_export_scl_pad_out               : out   std_logic;                                        -- scl_pad_out
			i2c_opencores_0_export_scl_pad_en                : out   std_logic;                                        -- scl_pad_en
			memory_mem_a                                     : out   std_logic_vector(14 downto 0);                    -- mem_a
			memory_mem_ba                                    : out   std_logic_vector(2 downto 0);                     -- mem_ba
			memory_mem_ck                                    : out   std_logic;                                        -- mem_ck
			memory_mem_ck_n                                  : out   std_logic;                                        -- mem_ck_n
			memory_mem_cke                                   : out   std_logic;                                        -- mem_cke
			memory_mem_cs_n                                  : out   std_logic;                                        -- mem_cs_n
			memory_mem_ras_n                                 : out   std_logic;                                        -- mem_ras_n
			memory_mem_cas_n                                 : out   std_logic;                                        -- mem_cas_n
			memory_mem_we_n                                  : out   std_logic;                                        -- mem_we_n
			memory_mem_reset_n                               : out   std_logic;                                        -- mem_reset_n
			memory_mem_dq                                    : inout std_logic_vector(31 downto 0) := (others => 'X'); -- mem_dq
			memory_mem_dqs                                   : inout std_logic_vector(3 downto 0)  := (others => 'X'); -- mem_dqs
			memory_mem_dqs_n                                 : inout std_logic_vector(3 downto 0)  := (others => 'X'); -- mem_dqs_n
			memory_mem_odt                                   : out   std_logic;                                        -- mem_odt
			memory_mem_dm                                    : out   std_logic_vector(3 downto 0);                     -- mem_dm
			memory_oct_rzqin                                 : in    std_logic                     := 'X';             -- oct_rzqin
			onboard_button_external_connection_export        : in    std_logic_vector(1 downto 0)  := (others => 'X'); -- export
			onboard_dipsw_external_connection_export         : in    std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			onboard_led_external_connection_export           : out   std_logic_vector(7 downto 0);                     -- export
			reset_reset_n                                    : in    std_logic                     := 'X';             -- reset_n
			rotary_encoder_0_conduit_end_rot_input           : in    std_logic                     := 'X';             -- rot_input
			spi_0_external_connection_MISO                   : in    std_logic                     := 'X';             -- MISO
			spi_0_external_connection_MOSI                   : out   std_logic;                                        -- MOSI
			spi_0_external_connection_SCLK                   : out   std_logic;                                        -- SCLK
			spi_0_external_connection_SS_n                   : out   std_logic_vector(2 downto 0);                     -- SS_n
			steering_pwm_pwm_signal_export                   : out   std_logic                                         -- export
		);
	end component Garfield_system;

	component altera_edge_detector is
		generic(
			PULSE_EXT             : natural := 0;
			EDGE_TYPE             : natural := 0;
			IGNORE_RST_WHILE_BUSY : natural := 0
		);
		port(
			clk       : in  std_logic;
			rst_n     : in  std_logic;
			signal_in : in  std_logic;
			pulse_out : out std_logic
		);
	end component;

	component hps_reset is
		port(
			probe      : in  std_logic;
			source_clk : in  std_logic;
			source     : out std_logic_vector(2 downto 0)
		);
	end component;

	----------------------------------------------------------------------------
    ---------------------- signals for top level logic
    ----------------------------------------------------------------------------
	signal hps_fpga_reset_n       : std_logic;
	signal fpga_debounced_buttons : std_logic_vector(1 downto 0);
	signal fpga_led_internal      : std_logic_vector(7 downto 0);
	signal hps_reset_req          : std_logic_vector(2 downto 0);
	signal hps_cold_reset         : std_logic;
	signal hps_warm_reset         : std_logic;
	signal hps_debug_reset        : std_logic;
	signal stm_hw_events          : std_logic_vector(27 downto 0);
	signal fpga_clk_50            : std_logic;
	signal spi_0_miso             : std_logic;
	signal spi_0_mosi             : std_logic;
	signal spi_0_sclk             : std_logic;
	signal spi_0_cs_n             : std_logic_vector(2 downto 0);
    signal i2c0_sda_i             : std_logic;
    signal i2c0_sda_o             : std_logic;
    signal i2c0_sda_en            : std_logic;
    signal i2c0_scl_i             : std_logic;
    signal i2c0_scl_o             : std_logic;
    signal i2c0_scl_en            : std_logic;

	signal garfield_lighting : std_logic_vector(3 downto 0);
	signal garfield_gpio     : std_logic_vector(7 downto 0);

	signal garfield_drive_pwm    : std_logic;
	signal garfield_steering_pwm : std_logic;
	signal speed_rotary          : std_logic;

    signal status_led            : std_logic := '0';
    signal status_led_counter    : natural := 0;

begin

	u0 : component Garfield_system
		port map(
			clk_clk                                          => FPGA_CLK1_50, -- clk.clk
			clk_1_fpga_clock_clk                             => FPGA_CLK2_50, -- clk_1_fpga_clock.clk
			clk_1_fpga_reset_reset_n                         => hps_fpga_reset_n, -- clk_1_fpga_reset.reset_n
			drive_pwm_pwm_signal_export                      => garfield_drive_pwm, -- drive_pwm_pwm_signal.export
			garfield_general_io_external_connection_export   => garfield_gpio, -- garfield_general_io_external_connection.export
			garfield_lighting_led_external_connection_export => garfield_lighting, -- garfield_lighting_led_external_connection.export
			hps_0_f2h_cold_reset_req_reset_n                 => not hps_cold_reset, -- hps_0_f2h_cold_reset_req.reset_n
			hps_0_f2h_debug_reset_req_reset_n                => not hps_debug_reset, -- hps_0_f2h_debug_reset_req.reset_n
			hps_0_f2h_stm_hw_events_stm_hwevents             => stm_hw_events, -- hps_0_f2h_stm_hw_events.stm_hwevents
			hps_0_f2h_warm_reset_req_reset_n                 => not hps_warm_reset, -- hps_0_f2h_warm_reset_req.reset_n
			hps_0_h2f_reset_reset_n                          => hps_fpga_reset_n, -- hps_0_h2f_reset.reset_n
			hps_0_hps_io_hps_io_emac1_inst_TX_CLK            => HPS_ENET_GTX_CLK, -- hps_0_hps_io.hps_io_emac1_inst_TX_CLK
			hps_0_hps_io_hps_io_emac1_inst_TXD0              => HPS_ENET_TX_DATA(0), -- .hps_io_emac1_inst_TXD0
			hps_0_hps_io_hps_io_emac1_inst_TXD1              => HPS_ENET_TX_DATA(1), -- .hps_io_emac1_inst_TXD1
			hps_0_hps_io_hps_io_emac1_inst_TXD2              => HPS_ENET_TX_DATA(2), -- .hps_io_emac1_inst_TXD2
			hps_0_hps_io_hps_io_emac1_inst_TXD3              => HPS_ENET_TX_DATA(3), -- .hps_io_emac1_inst_TXD3
			hps_0_hps_io_hps_io_emac1_inst_RXD0              => HPS_ENET_RX_DATA(0), -- .hps_io_emac1_inst_RXD0
			hps_0_hps_io_hps_io_emac1_inst_MDIO              => HPS_ENET_MDIO, -- .hps_io_emac1_inst_MDIO
			hps_0_hps_io_hps_io_emac1_inst_MDC               => HPS_ENET_MDC, -- .hps_io_emac1_inst_MDC
			hps_0_hps_io_hps_io_emac1_inst_RX_CTL            => HPS_ENET_RX_DV, -- .hps_io_emac1_inst_RX_CTL
			hps_0_hps_io_hps_io_emac1_inst_TX_CTL            => HPS_ENET_TX_EN, -- .hps_io_emac1_inst_TX_CTL
			hps_0_hps_io_hps_io_emac1_inst_RX_CLK            => HPS_ENET_RX_CLK, -- .hps_io_emac1_inst_RX_CLK
			hps_0_hps_io_hps_io_emac1_inst_RXD1              => HPS_ENET_RX_DATA(1), -- .hps_io_emac1_inst_RXD1
			hps_0_hps_io_hps_io_emac1_inst_RXD2              => HPS_ENET_RX_DATA(2), -- .hps_io_emac1_inst_RXD2
			hps_0_hps_io_hps_io_emac1_inst_RXD3              => HPS_ENET_RX_DATA(3), -- .hps_io_emac1_inst_RXD3
			hps_0_hps_io_hps_io_sdio_inst_CMD                => HPS_SD_CMD, -- .hps_io_sdio_inst_CMD
			hps_0_hps_io_hps_io_sdio_inst_D0                 => HPS_SD_DATA(0), -- .hps_io_sdio_inst_D0
			hps_0_hps_io_hps_io_sdio_inst_D1                 => HPS_SD_DATA(1), -- .hps_io_sdio_inst_D1
			hps_0_hps_io_hps_io_sdio_inst_CLK                => HPS_SD_CLK, -- .hps_io_sdio_inst_CLK
			hps_0_hps_io_hps_io_sdio_inst_D2                 => HPS_SD_DATA(2), -- .hps_io_sdio_inst_D2
			hps_0_hps_io_hps_io_sdio_inst_D3                 => HPS_SD_DATA(3), -- .hps_io_sdio_inst_D3
			hps_0_hps_io_hps_io_usb1_inst_D0                 => HPS_USB_DATA(0), -- .hps_io_usb1_inst_D0
			hps_0_hps_io_hps_io_usb1_inst_D1                 => HPS_USB_DATA(1), -- .hps_io_usb1_inst_D1
			hps_0_hps_io_hps_io_usb1_inst_D2                 => HPS_USB_DATA(2), -- .hps_io_usb1_inst_D2
			hps_0_hps_io_hps_io_usb1_inst_D3                 => HPS_USB_DATA(3), -- .hps_io_usb1_inst_D3
			hps_0_hps_io_hps_io_usb1_inst_D4                 => HPS_USB_DATA(4), -- .hps_io_usb1_inst_D4
			hps_0_hps_io_hps_io_usb1_inst_D5                 => HPS_USB_DATA(5), -- .hps_io_usb1_inst_D5
			hps_0_hps_io_hps_io_usb1_inst_D6                 => HPS_USB_DATA(6), -- .hps_io_usb1_inst_D6
			hps_0_hps_io_hps_io_usb1_inst_D7                 => HPS_USB_DATA(7), -- .hps_io_usb1_inst_D7
			hps_0_hps_io_hps_io_usb1_inst_CLK                => HPS_USB_CLKOUT, -- .hps_io_usb1_inst_CLK
			hps_0_hps_io_hps_io_usb1_inst_STP                => HPS_USB_STP, -- .hps_io_usb1_inst_STP
			hps_0_hps_io_hps_io_usb1_inst_DIR                => HPS_USB_DIR, -- .hps_io_usb1_inst_DIR
			hps_0_hps_io_hps_io_usb1_inst_NXT                => HPS_USB_NXT, -- .hps_io_usb1_inst_NXT
			hps_0_hps_io_hps_io_spim1_inst_CLK               => HPS_SPIM_CLK, -- .hps_io_spim1_inst_CLK
			hps_0_hps_io_hps_io_spim1_inst_MOSI              => HPS_SPIM_MOSI, -- .hps_io_spim1_inst_MOSI
			hps_0_hps_io_hps_io_spim1_inst_MISO              => HPS_SPIM_MISO, -- .hps_io_spim1_inst_MISO
			hps_0_hps_io_hps_io_spim1_inst_SS0               => HPS_SPIM_SS, -- .hps_io_spim1_inst_SS0
			hps_0_hps_io_hps_io_uart0_inst_RX                => HPS_UART_RX, -- .hps_io_uart0_inst_RX
			hps_0_hps_io_hps_io_uart0_inst_TX                => HPS_UART_TX, -- .hps_io_uart0_inst_TX
			hps_0_hps_io_hps_io_i2c0_inst_SDA                => HPS_I2C0_SDAT, -- .hps_io_i2c0_inst_SDA
			hps_0_hps_io_hps_io_i2c0_inst_SCL                => HPS_I2C0_SCLK, -- .hps_io_i2c0_inst_SCL
			hps_0_hps_io_hps_io_i2c1_inst_SDA                => HPS_I2C1_SDAT, -- .hps_io_i2c1_inst_SDA
			hps_0_hps_io_hps_io_i2c1_inst_SCL                => HPS_I2C1_SCLK, -- .hps_io_i2c1_inst_SCL
			hps_0_hps_io_hps_io_gpio_inst_GPIO09             => HPS_CONV_USB_N, -- .hps_io_gpio_inst_GPIO09
			hps_0_hps_io_hps_io_gpio_inst_GPIO35             => HPS_ENET_INT_N, -- .hps_io_gpio_inst_GPIO35
			hps_0_hps_io_hps_io_gpio_inst_GPIO40             => HPS_LTC_GPIO, -- .hps_io_gpio_inst_GPIO40
			hps_0_hps_io_hps_io_gpio_inst_GPIO53             => HPS_LED, -- .hps_io_gpio_inst_GPIO53
			hps_0_hps_io_hps_io_gpio_inst_GPIO54             => HPS_KEY, -- .hps_io_gpio_inst_GPIO54
			hps_0_hps_io_hps_io_gpio_inst_GPIO61             => HPS_GSENSOR_INT, -- .hps_io_gpio_inst_GPIO61
			memory_mem_a                                     => HPS_DDR3_ADDR, -- memory.mem_a
			memory_mem_ba                                    => HPS_DDR3_BA, -- .mem_ba
			memory_mem_ck                                    => HPS_DDR3_CK_P, -- .mem_ck
			memory_mem_ck_n                                  => HPS_DDR3_CK_N, -- .mem_ck_n
			memory_mem_cke                                   => HPS_DDR3_CKE, -- .mem_cke
			memory_mem_cs_n                                  => HPS_DDR3_CS_N, -- .mem_cs_n
			memory_mem_ras_n                                 => HPS_DDR3_RAS_N, -- .mem_ras_n
			memory_mem_cas_n                                 => HPS_DDR3_CAS_N, -- .mem_cas_n
			memory_mem_we_n                                  => HPS_DDR3_WE_N, -- .mem_we_n
			memory_mem_reset_n                               => HPS_DDR3_RESET_N, -- .mem_reset_n
			memory_mem_dq                                    => HPS_DDR3_DQ, -- .mem_dq
			memory_mem_dqs                                   => HPS_DDR3_DQS_P, -- .mem_dqs
			memory_mem_dqs_n                                 => HPS_DDR3_DQS_N, -- .mem_dqs_n
			memory_mem_odt                                   => HPS_DDR3_ODT, -- .mem_odt
			memory_mem_dm                                    => HPS_DDR3_DM, -- .mem_dm
			memory_oct_rzqin                                 => HPS_DDR3_RZQ, -- .oct_rzqin
			onboard_button_external_connection_export        => fpga_debounced_buttons, -- onboard_button_external_connection.export
			onboard_dipsw_external_connection_export         => SW, -- onboard_dipsw_external_connection.export
			onboard_led_external_connection_export           => fpga_led_internal, -- onboard_led_external_connection.export
			reset_reset_n                                    => hps_fpga_reset_n, -- reset.reset_n
			rotary_encoder_0_conduit_end_rot_input           => speed_rotary, -- rotary_encoder_0_conduit_end.rot_input
			spi_0_external_connection_MISO                   => spi_0_miso, -- spi_0_external_connection.MISO
			spi_0_external_connection_MOSI                   => spi_0_mosi, -- .MOSI
			spi_0_external_connection_SCLK                   => spi_0_sclk, -- .SCLK
			spi_0_external_connection_SS_n                   => spi_0_cs_n, -- .SS_n
			steering_pwm_pwm_signal_export                   => garfield_steering_pwm, -- steering_pwm_pwm_signal.export
            i2c_opencores_0_export_sda_pad_in                => i2c0_sda_i,             -- sda_pad_in
			i2c_opencores_0_export_sda_pad_out               => i2c0_sda_o,                                        -- sda_pad_out
			i2c_opencores_0_export_sda_pad_en                => i2c0_sda_en,                                        -- sda_pad_en
			i2c_opencores_0_export_scl_pad_in                => i2c0_scl_i,             -- scl_pad_in
			i2c_opencores_0_export_scl_pad_out               => i2c0_scl_o,                                        -- scl_pad_out
			i2c_opencores_0_export_scl_pad_en                => i2c0_scl_en
        );

	pulse_cold_reset : component altera_edge_detector
		generic map(
			PULSE_EXT             => 6,
			EDGE_TYPE             => 1,
			IGNORE_RST_WHILE_BUSY => 1
		)
		port map(
			clk       => fpga_clk_50,
			rst_n     => hps_fpga_reset_n,
			signal_in => hps_reset_req(0),
			pulse_out => hps_cold_reset
		);

	pulse_warm_reset : component altera_edge_detector
		generic map(
			PULSE_EXT             => 2,
			EDGE_TYPE             => 1,
			IGNORE_RST_WHILE_BUSY => 1
		)
		port map(
			clk       => fpga_clk_50,
			rst_n     => hps_fpga_reset_n,
			signal_in => hps_reset_req(1),
			pulse_out => hps_warm_reset
		);

	pulse_debug_reset : component altera_edge_detector
		generic map(
			PULSE_EXT             => 32,
			EDGE_TYPE             => 1,
			IGNORE_RST_WHILE_BUSY => 1
		)
		port map(
			clk       => fpga_clk_50,
			rst_n     => hps_fpga_reset_n,
			signal_in => hps_reset_req(2),
			pulse_out => hps_debug_reset
		);

	----------------------------------------------------------------------------
    -- concurrent statements
    ----------------------------------------------------------------------------

    -- i2c0
	GPIO_1(0)  <= 'Z' when i2c0_sda_en = '1' else i2c0_sda_o;
	GPIO_1(2)  <= 'Z' when i2c0_scl_en = '1' else i2c0_scl_o;
    i2c0_sda_i <= GPIO_1(0);
    i2c0_scl_i <= GPIO_1(2);
    -- garfield lighting
    GPIO_1(1) <= garfield_lighting(0);
    GPIO_1(3) <= garfield_lighting(1);
    GPIO_1(5) <= garfield_lighting(2);
    GPIO_1(7) <= garfield_lighting(3);
    -- spi for display
    ARDUINO_IO(13) <= spi_0_sclk;
    ARDUINO_IO(12) <= spi_0_miso;
    ARDUINO_IO(11) <= spi_0_mosi;
    ARDUINO_IO(10) <= spi_0_cs_n(0);   -- tft chipselect
    ARDUINO_IO(9) <= garfield_gpio(7); -- tft data command switch
    ARDUINO_IO(4) <= spi_0_cs_n(1);    -- sd card chipselect
    -- pwm's and rotary of garfield
    GPIO_1(4) <= garfield_drive_pwm;
    GPIO_1(9) <= garfield_steering_pwm;
    speed_rotary <= GPIO_1(11);


    -- others
	stm_hw_events <= (others => '0');
    fpga_clk_50 <= FPGA_CLK1_50;
    LED(7 downto 1) <= fpga_led_internal(7 downto 1);
    LED(0) <= status_led;

    ----------------------------------------------------------------------------
    -- processes
    ----------------------------------------------------------------------------

    status_led_proc : process(fpga_clk_50, hps_fpga_reset_n) is
    begin
        if (hps_fpga_reset_n = '0') then
            status_led_counter <= 0;
        elsif (rising_edge(fpga_clk_50)) then
            if status_led_counter = 24999999 then
                status_led <= not status_led;
                status_led_counter <= 0;
            else
                status_led_counter <= status_led_counter + 1;
             end if;
        end if;
    end process status_led_proc;


end architecture RTL;
