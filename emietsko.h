/***************************************************************************

  Emi Etsuko
  (c) 1982 EmiDev

  Hardware: Konami Scramble Hardware
  Header File for MAME 0.139u1

***************************************************************************/

#ifndef __EMIETSKO_H__
#define __EMIETSKO_H__

#include "emu.h"
#include "machine/8255ppi.h"

/* --- Driver State Class --- */
class emietsko_state : public driver_device
{
public:
	emietsko_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag) { }

	/* Memory pointers */
	UINT8 *  m_videoram;
	UINT8 *  m_spriteram;
	UINT8 *  m_attributesram;
	UINT8 *  m_bulletsram;
	size_t   m_spriteram_size;
	size_t   m_bulletsram_size;

	/* Video state */
	UINT8    m_nmi_enabled;
	UINT8    m_flip_screen_x;
	UINT8    m_flip_screen_y;
	UINT8    m_stars_enabled;

	/* Sound state */
	UINT8    m_sound_nmi_enabled;
};

/* --- External Declarations from Galaxian/Scramble hardware --- */

/* Video functions */
PALETTE_INIT( galaxold );
VIDEO_START( galaxold );
VIDEO_UPDATE( galaxold );

/* Memory handlers */
WRITE8_HANDLER( galaxold_videoram_w );
WRITE8_HANDLER( galaxold_attributesram_w );
WRITE8_HANDLER( galaxold_flip_screen_x_w );
WRITE8_HANDLER( galaxold_flip_screen_y_w );
WRITE8_HANDLER( galaxold_nmi_enable_w );
WRITE8_HANDLER( galaxold_coin_counter_w );
WRITE8_HANDLER( galaxold_stars_enable_w );

/* PPI Interfaces */
extern const ppi8255_interface scramble_ppi8255_0_intf;
extern const ppi8255_interface scramble_ppi8255_1_intf;

/* Sound handlers */
WRITE8_HANDLER( ay8910_address_0_w );
WRITE8_HANDLER( ay8910_data_0_w );
READ8_HANDLER( ay8910_read_port_0_r );
WRITE8_HANDLER( ay8910_address_1_w );
WRITE8_HANDLER( ay8910_data_1_w );
READ8_HANDLER( ay8910_read_port_1_r );

#endif /* __EMIETSKO_H__ */
