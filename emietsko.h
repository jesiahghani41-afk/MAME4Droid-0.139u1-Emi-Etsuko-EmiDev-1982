/***************************************************************************

  Emi Etsuko
  (c) 1982 EmiDev

  Hardware: Konami Scramble Hardware
  Header File

***************************************************************************/

#ifndef __EMIETSKO_H__
#define __EMIETSKO_H__

#include "machine/8255ppi.h"

class emietsko_state : public driver_device
{
public:
	emietsko_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag) { }

	/* devices */
	device_t *m_maincpu;
	device_t *m_audiocpu;
	device_t *m_ppi8255_0;
	device_t *m_ppi8255_1;

	/* video-related */
	UINT8 *  m_videoram;
	UINT8 *  m_spriteram;
	UINT8 *  m_attributesram;
	UINT8 *  m_bulletsram;
	size_t   m_spriteram_size;
	size_t   m_bulletsram_size;

	UINT8    m_nmi_enabled;
	UINT8    m_flip_screen_x;
	UINT8    m_flip_screen_y;
	UINT8    m_stars_enabled;

	/* sound-related */
	UINT8    m_sound_nmi_enabled;
};

/* -------- Prototype Declarations -------- */

/* Video */
PALETTE_INIT( galaxold );
VIDEO_START( galaxold );
VIDEO_UPDATE( galaxold );

WRITE8_HANDLER( galaxold_videoram_w );
WRITE8_HANDLER( galaxold_attributesram_w );
WRITE8_HANDLER( galaxold_flip_screen_x_w );
WRITE8_HANDLER( galaxold_flip_screen_y_w );

/* Machine / PPI */
extern const ppi8255_interface scramble_ppi8255_0_intf;
extern const ppi8255_interface scramble_ppi8255_1_intf;

#endif /* __EMIETSKO_H__ */
