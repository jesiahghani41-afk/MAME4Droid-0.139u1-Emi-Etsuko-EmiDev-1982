/***************************************************************************

  Emi Etsuko
  (c) 1982 EmiDev

  Hardware: Konami Scramble Hardware
  Genre: Action/Platform (Vertical Screen)
  Players: 1-2
  Control: 4-Way Joystick, 1 Button
  
  MAME 0.139u1 Driver Integration

***************************************************************************/

#include "emu.h"
#include "cpu/z80/z80.h"
#include "cpu/s2650/s2650.h"
#include "sound/ay8910.h"
#include "machine/8255ppi.h"
#include "includes/galaxold.h"
#include "emietsko.h"

/* ----------------- Memory Maps ----------------- */

static ADDRESS_MAP_START( emietsko_map, ADDRESS_SPACE_PROGRAM, 8 )
	AM_RANGE(0x0000, 0x3fff) AM_ROM
	AM_RANGE(0x4000, 0x47ff) AM_RAM
	AM_RANGE(0x4800, 0x4bff) AM_RAM_WRITE(galaxold_videoram_w) AM_BASE(&galaxold_videoram)
	AM_RANGE(0x4c00, 0x4fff) AM_READWRITE(galaxold_videoram_r, galaxold_videoram_w)	/* mirror address */
	AM_RANGE(0x5000, 0x503f) AM_RAM_WRITE(galaxold_attributesram_w) AM_BASE(&galaxold_attributesram)
	AM_RANGE(0x5040, 0x505f) AM_RAM AM_BASE(&galaxold_spriteram) AM_SIZE(&galaxold_spriteram_size)
	AM_RANGE(0x5060, 0x507f) AM_RAM AM_BASE(&galaxold_bulletsram) AM_SIZE(&galaxold_bulletsram_size)
	AM_RANGE(0x5080, 0x50ff) AM_RAM
	AM_RANGE(0x6801, 0x6801) AM_WRITE(galaxold_nmi_enable_w)
	AM_RANGE(0x6802, 0x6802) AM_WRITE(galaxold_coin_counter_w)
	AM_RANGE(0x6804, 0x6804) AM_WRITE(galaxold_stars_enable_w)
	AM_RANGE(0x6806, 0x6806) AM_WRITE(galaxold_flip_screen_x_w)
	AM_RANGE(0x6807, 0x6807) AM_WRITE(galaxold_flip_screen_y_w)
	AM_RANGE(0x7000, 0x7000) AM_READ(watchdog_reset_r)
	AM_RANGE(0x8100, 0x8103) AM_DEVREADWRITE("ppi8255_0", ppi8255_r, ppi8255_w)
	AM_RANGE(0x8200, 0x8203) AM_DEVREADWRITE("ppi8255_1", ppi8255_r, ppi8255_w)
ADDRESS_MAP_END

static ADDRESS_MAP_START( emietsko_sound_map, ADDRESS_SPACE_PROGRAM, 8 )
	AM_RANGE(0x0000, 0x1fff) AM_ROM
	AM_RANGE(0x8000, 0x83ff) AM_RAM
ADDRESS_MAP_END

static ADDRESS_MAP_START( emietsko_sound_io_map, ADDRESS_SPACE_IO, 8 )
	AM_RANGE(0x10, 0x10) AM_WRITE(ay8910_address_0_w)
	AM_RANGE(0x20, 0x20) AM_READWRITE(ay8910_read_port_0_r, ay8910_data_0_w)
	AM_RANGE(0x40, 0x40) AM_WRITE(ay8910_address_1_w)
	AM_RANGE(0x80, 0x80) AM_READWRITE(ay8910_read_port_1_r, ay8910_data_1_w)
ADDRESS_MAP_END

/* ----------------- Input Ports ----------------- */

static INPUT_PORTS_START( emietsko )
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_4WAY
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_BUTTON2 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_BUTTON1 )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_4WAY
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_4WAY
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_COIN1 )

	PORT_START("IN1")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_DIPSWITCH_NAME ) PORT_NAME("DIP SW 1") PORT_CODE(KEYCODE_F1)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_4WAY PORT_COCKTAIL
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_4WAY PORT_COCKTAIL
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_COCKTAIL
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_4WAY PORT_COCKTAIL
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_4WAY PORT_COCKTAIL
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_START2 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START1 )

	PORT_START("IN2")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_4WAY
	PORT_DIPNAME( 0x06, 0x00, DEF_STR( Lives ) )
	PORT_DIPSETTING(    0x00, "3" )
	PORT_DIPSETTING(    0x02, "4" )
	PORT_DIPSETTING(    0x04, "5" )
	PORT_DIPSETTING(    0x06, "255 (Cheat)" )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_COCKTAIL
	PORT_DIPNAME( 0x10, 0x00, DEF_STR( Cabinet ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Upright ) )
	PORT_DIPSETTING(    0x10, DEF_STR( Cocktail ) )
	PORT_DIPNAME( 0x20, 0x00, "Unknown" )
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x20, DEF_STR( On ) )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )
INPUT_PORTS_END

/* ----------------- Machine Driver ----------------- */

static MACHINE_DRIVER_START( emietsko )
	/* basic machine hardware */
	MDRV_CPU_ADD("maincpu", Z80, 18432000/6)	/* 3.072 MHz */
	MDRV_CPU_PROGRAM_MAP(emietsko_map)
	MDRV_CPU_VBLANK_INT("screen", nmi_line_pulse)

	MDRV_CPU_ADD("audiocpu", Z80, 14318180/8)	/* 1.789772 MHz */
	MDRV_CPU_PROGRAM_MAP(emietsko_sound_map)
	MDRV_CPU_IO_MAP(emietsko_sound_io_map)

	MDRV_PPI8255_ADD( "ppi8255_0", scramble_ppi8255_0_intf )
	MDRV_PPI8255_ADD( "ppi8255_1", scramble_ppi8255_1_intf )

	/* video hardware */
	MDRV_SCREEN_ADD("screen", RASTER)
	MDRV_SCREEN_REFRESH_RATE(16000.0/132/128.0)
	MDRV_SCREEN_VBLANK_TIME(ATTOSECONDS_IN_USEC(0))
	MDRV_SCREEN_FORMAT(BITMAP_FORMAT_INDEXED16)
	MDRV_SCREEN_SIZE(32*8, 32*8)
	MDRV_SCREEN_VISIBLE_AREA(0*8, 32*8-1, 2*8, 30*8-1)

	MDRV_GFXDECODE(galaxold)
	MDRV_PALETTE_LENGTH(32)

	MDRV_PALETTE_INIT(galaxold)
	MDRV_VIDEO_START(galaxold)
	MDRV_VIDEO_UPDATE(galaxold)

	/* sound hardware */
	MDRV_SPEAKER_STANDARD_MONO("mono")
	MDRV_SOUND_ADD("ay1", AY8910, 14318180/8)
	MDRV_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.50)
	MDRV_SOUND_ADD("ay2", AY8910, 14318180/8)
	MDRV_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.50)
MACHINE_DRIVER_END

/* ----------------- ROM Definitions ----------------- */

ROM_START( emietsko )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "emi_cpu.bin",  0x0000, 0x4000, CRC(00000000) SHA1(0000000000000000000000000000000000000000) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "emi_snd.bin",  0x0000, 0x1000, CRC(00000000) SHA1(0000000000000000000000000000000000000000) )

	ROM_REGION( 0x2000, "gfx1", 0 )
	ROM_LOAD( "emi_gfx1.bin", 0x0000, 0x1000, CRC(00000000) SHA1(0000000000000000000000000000000000000000) )
	ROM_LOAD( "emi_gfx2.bin", 0x1000, 0x1000, CRC(00000000) SHA1(0000000000000000000000000000000000000000) )

	ROM_REGION( 0x0020, "proms", 0 )
	ROM_LOAD( "emi_clr.bin",  0x0000, 0x0020, CRC(00000000) SHA1(0000000000000000000000000000000000000000) )
ROM_END

/* ----------------- Game Driver ----------------- */

GAME( 1982, emietsko, 0, emietsko, emietsko, 0, ROT90, "EmiDev", "Emi Etsuko", GAME_SUPPORTS_SAVE )
