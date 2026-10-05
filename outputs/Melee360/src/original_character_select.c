/* Original CSS core excerpts with an isolated single-player platform boundary.
 * The complete original scene, audio, tags, CPUs and costume logic are pending. */
#ifndef LINT
#define LINT 1
#endif
#include "../compat/gameplay_boundary.h"
#include <melee/mn/types.h>
#include <sysdolphin/baselib/controller.h>
#include "original_character_select.h"
#include <string.h>
static CSSData css;
static CSSData* mnCharSel_804D6CB0=&css;
static CSSDoorsData mnCharSel_803F0DFC;
static u8 mnCharSel_804D6CF5=4;
static s8 mnCharSel_804D6CF0=0,mnCharSel_804D6CF1=1;
static struct CSSCursorData* mnCharSel_804A0BC0[4];
static struct CSSCharModel* mnCharSel_804A0BD0[4];
static HSD_PadStatus cssPads[4];
#define HSD_PadCopyStatus cssPads
extern float Melee360CSSAtan2f(float, float);
#undef atan2f
#define atan2f Melee360CSSAtan2f
#include "../compat/generated/original_css.inc"
#undef atan2f
#undef HSD_PadCopyStatus
ASSERT_SIZE(CSSData,0x148);
ASSERT_SIZE(CSSIcon,0x1C);
ASSERT_SIZE(struct CSSCursorData,0x14);
ASSERT_SIZE(struct CSSCharModel,0x18);
static struct CSSCursorData cursor;
static struct CSSCharModel token;
static int hovered,confirmed;
void Melee360CSSInit(void){int i;memset(&css,0,sizeof(css));memset(&mnCharSel_803F0DFC,0,sizeof(mnCharSel_803F0DFC));memset(&cursor,0,sizeof(cursor));memset(&token,0,sizeof(token));memset(cssPads,0,sizeof(cssPads));
    for(i=0;i<4;++i){mnCharSel_804A0BC0[i]=&cursor;mnCharSel_804A0BD0[i]=&token;css.vs.start.players[i].ckind=ChKind_None;mnCharSel_803F0DFC.doors[i].p_kind=i?3:0;}
    // Preserve the current diagnostic's exposed roster; save unlocks are pending.
    for(i=0;i<25;++i)if(icons[i].state==0)icons[i].state=ICONSTATE_TEMP;
    cursor.x4=0;cursor.x5=1;token.x4=0;token.x5=1;originalPlaceToken(0,1);token.x10=token.x8;token.x14=token.xC;cursor.xC=token.x8-2.7f;cursor.x10=token.xC+2;
    hovered=1;confirmed=0;mnCharSel_803F0DFC.doors[0].sel_icon=1;
}
void Melee360CSSAdvance(int stickX,int stickY){f32 dx,dy;cssPads[0].stickX=(s8)(stickX<-127?-127:stickX>127?127:stickX);cssPads[0].stickY=(s8)(stickY<-127?-127:stickY>127?127:stickY);getStickDelta(0,&dx,&dy);originalMove(&cursor,dx,dy);
    if(!confirmed){originalFollow(&token);hovered=originalHit(&token);if(hovered>=0)mnCharSel_803F0DFC.doors[0].sel_icon=(u8)hovered;}
    originalSmooth(&token);
}
int Melee360CSSConfirm(void){int door=0;if(confirmed||hovered<0)return 0;originalStoreCharacter(door);icons[hovered].anim_timer=0xC;mnCharSel_803F0DFC.doors[door].sel_icon_prev=(u8)hovered;mnCharSel_803F0DFC.doors[door].selected_since_load=1;token.x5=0;cursor.x5=2;confirmed=1;return 1;}
void Melee360CSSRetrieve(void){if(!confirmed)return;originalPlaceToken(0,mnCharSel_803F0DFC.doors[0].sel_icon);cursor.xC=token.x8-2.7f;cursor.x10=token.xC+2;cursor.x5=1;token.x5=1;confirmed=0;hovered=mnCharSel_803F0DFC.doors[0].sel_icon;}
void Melee360CSSGetState(struct Melee360CSSState* s){s->handX=cursor.xC;s->handY=cursor.x10;s->tokenX=token.x10;s->tokenY=token.x14;s->hover=hovered;s->selected=mnCharSel_803F0DFC.doors[0].sel_icon;s->confirmed=confirmed;s->ckind=css.vs.start.players[0].ckind;s->handState=cursor.x5;}
int Melee360CSSPortraitFrame(int icon){return icon>=0&&icon<25?icons[icon].ft_hudindex:-1;}
int Melee360CSSPlaceAtIcon(int icon){if(icon<0||icon>=25||confirmed)return 0;originalPlaceToken(0,icon);cursor.xC=token.x8-2.7f;cursor.x10=token.xC+2;token.x10=token.x8;token.x14=token.xC;Melee360CSSAdvance(0,0);return hovered==icon;}
int Melee360CSSProbe(void){int i,k;struct Melee360CSSState s;Melee360CSSInit();for(i=0;i<25;++i){if(!Melee360CSSPlaceAtIcon(i)||!Melee360CSSConfirm())return 0;Melee360CSSGetState(&s);if(!s.confirmed||s.ckind!=icons[i].char_kind)return 0;Melee360CSSAdvance(80,0);Melee360CSSGetState(&s);if(s.selected!=i||s.ckind!=icons[i].char_kind)return 0;Melee360CSSRetrieve();}
    Melee360CSSInit();for(k=0;k<120;++k)Melee360CSSAdvance(127,127);Melee360CSSGetState(&s);if(s.handX!=26||s.handY!=25||s.hover!=-1||Melee360CSSConfirm())return 0;for(k=0;k<120;++k)Melee360CSSAdvance(-127,-127);Melee360CSSGetState(&s);if(s.handX!=-35||s.handY!=-22)return 0;Melee360CSSInit();return 1;}
