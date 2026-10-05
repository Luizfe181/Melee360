#ifndef MELEE360_ORIGINAL_CSS_H
#define MELEE360_ORIGINAL_CSS_H
#ifdef __cplusplus
extern "C" {
#endif
struct Melee360CSSState {float handX,handY,tokenX,tokenY;int hover,selected,confirmed,ckind,handState;};
void Melee360CSSInit(void);
void Melee360CSSAdvance(int stickX,int stickY);
int Melee360CSSConfirm(void);
void Melee360CSSRetrieve(void);
void Melee360CSSGetState(struct Melee360CSSState* state);
int Melee360CSSPortraitFrame(int icon);
int Melee360CSSPlaceAtIcon(int icon); /* Diagnostic input injection only. */
int Melee360CSSProbe(void);
#ifdef __cplusplus
}
#endif
#endif
