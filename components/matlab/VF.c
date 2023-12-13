/*
 * File: VF.c
 *
 * Code generated for Simulink model 'VF'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Nov  6 02:11:37 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: RISC-V->RV32I
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "VF.h"

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;
static uint32_T plook_u32ff_evencg(real32_T u, real32_T bp0, real32_T bpSpace,
  uint32_T maxIndex, real32_T *fraction);
static real32_T intrp1d_fu32fl(uint32_T bpIndex, real32_T frac, const real32_T
  table[]);
static void SVPWM(real32_T rtu_Valpha, real32_T rtu_Vbeta, real32_T rtu_v_bus,
                  real32_T rty_tABC[3]);
static void VFmode(void);
static uint32_T plook_u32ff_evencg(real32_T u, real32_T bp0, real32_T bpSpace,
  uint32_T maxIndex, real32_T *fraction)
{
  real32_T fbpIndex;
  real32_T invSpc;
  uint32_T bpIndex;

  /* Prelookup - Index and Fraction
     Index Search method: 'even'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'on'
   */
  invSpc = 1.0F / bpSpace;
  fbpIndex = (u - bp0) * invSpc;
  if (fbpIndex < maxIndex) {
    bpIndex = (uint32_T)fbpIndex;
    *fraction = (u - ((real32_T)(uint32_T)fbpIndex * bpSpace + bp0)) * invSpc;
  } else {
    bpIndex = maxIndex - 1U;
    *fraction = 1.0F;
  }

  return bpIndex;
}

static real32_T intrp1d_fu32fl(uint32_T bpIndex, real32_T frac, const real32_T
  table[])
{
  real32_T yL_0d0;

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  yL_0d0 = table[bpIndex];
  return (table[bpIndex + 1U] - yL_0d0) * frac + yL_0d0;
}

/* Output and update for atomic system: '<S1>/SVPWM' */
static void SVPWM(real32_T rtu_Valpha, real32_T rtu_Vbeta, real32_T rtu_v_bus,
                  real32_T rty_tABC[3])
{
  real32_T rtb_Min;
  real32_T rtb_Sum1_j;
  real32_T rtb_Sum_p;

  /* Gain: '<S9>/Gain' */
  rtb_Min = -0.5F * rtu_Valpha;

  /* Gain: '<S9>/Gain1' */
  rtb_Sum1_j = 0.866025388F * rtu_Vbeta;

  /* Sum: '<S9>/Sum' */
  rtb_Sum_p = rtb_Min + rtb_Sum1_j;

  /* Sum: '<S9>/Sum1' */
  rtb_Sum1_j = rtb_Min - rtb_Sum1_j;

  /* Gain: '<S10>/Gain' incorporates:
   *  MinMax: '<S10>/Min'
   *  MinMax: '<S10>/Min1'
   *  Sum: '<S10>/Sum'
   */
  rtb_Min = (fminf(fminf(rtu_Valpha, rtb_Sum_p), rtb_Sum1_j) + fmaxf(fmaxf
              (rtu_Valpha, rtb_Sum_p), rtb_Sum1_j)) * -0.5F;

  /* Sum: '<S4>/Sum' */
  rty_tABC[0] = rtb_Min + rtu_Valpha;
  rty_tABC[1] = rtb_Min + rtb_Sum_p;
  rty_tABC[2] = rtb_Min + rtb_Sum1_j;

  /* Gain: '<S4>/PWM_HalfPeriod' incorporates:
   *  Constant: '<S4>/Constant'
   *  Gain: '<S4>/Gain'
   *  Product: '<S4>/Divide'
   *  Sum: '<S4>/Sum1'
   */
  rty_tABC[0] = (-rty_tABC[0] / rtu_v_bus + 0.5F) * 1023.0F;
  rty_tABC[1] = (-rty_tABC[1] / rtu_v_bus + 0.5F) * 1023.0F;
  rty_tABC[2] = (-rty_tABC[2] / rtu_v_bus + 0.5F) * 1023.0F;
}

/* Output and update for atomic system: '<Root>/VF mode' */
static void VFmode(void)
{
  real32_T frac;
  real32_T rtb_Sum;
  real32_T uVarTmp;
  real32_T uVarTmp_0;
  real32_T yVarTmp;
  uint32_T bpIdx;
  boolean_T negFlag;
  static const real32_T tableData_c[16] = { 0.0F, 0.104528464F, 0.207911685F,
    0.309017F, 0.406736642F, 0.5F, 0.587785244F, 0.669130623F, 0.74314481F,
    0.809017F, 0.866025388F, 0.91354543F, 0.95105654F, 0.978147626F,
    0.994521916F, 1.0F };

  /* Sum: '<S3>/Sum' incorporates:
   *  Gain: '<S3>/Gain'
   *  Inport: '<Root>/Freq'
   *  UnitDelay: '<S3>/Unit Delay'
   */
  rtb_Sum = 0.000628318521F * rtU.Freq + rtDW.UnitDelay_DSTATE;

  /* If: '<S5>/If' incorporates:
   *  Constant: '<S5>/Constant'
   *  Constant: '<S5>/Constant1'
   *  RelationalOperator: '<S5>/Relational Operator'
   *  RelationalOperator: '<S5>/Relational Operator1'
   */
  if (rtb_Sum > 6.28318548F) {
    /* Outputs for IfAction SubSystem: '<S5>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    /* Sum: '<S6>/Sum' incorporates:
     *  Constant: '<S6>/Constant'
     */
    rtb_Sum -= 6.28318548F;

    /* End of Outputs for SubSystem: '<S5>/If Action Subsystem1' */
  } else if (rtb_Sum < 0.0F) {
    /* Outputs for IfAction SubSystem: '<S5>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S8>/Action Port'
     */
    /* Sum: '<S8>/Sum' incorporates:
     *  Constant: '<S8>/Constant'
     */
    rtb_Sum += 6.28318548F;

    /* End of Outputs for SubSystem: '<S5>/If Action Subsystem3' */
  }

  /* End of If: '<S5>/If' */

  /* Trigonometry: '<S1>/SinCos1' incorporates:
   *  Trigonometry: '<S1>/SinCos'
   */
  yVarTmp = rtb_Sum / 6.28318548F;
  uVarTmp = rtb_Sum / 6.28318548F + 0.25F;
  if (yVarTmp + 0.25F >= 1.0F) {
    uVarTmp = (yVarTmp + 0.25F) - 1.0F;
  }

  if (uVarTmp < 0.0F) {
    uVarTmp_0 = uVarTmp + 1.0F;
  } else {
    uVarTmp_0 = uVarTmp;
  }

  if (uVarTmp_0 > 0.5F) {
    uVarTmp_0 -= 0.5F;
    negFlag = true;
  } else {
    negFlag = false;
  }

  if (uVarTmp_0 > 0.25F) {
    uVarTmp_0 = 0.5F - uVarTmp_0;
  }

  bpIdx = plook_u32ff_evencg(uVarTmp_0, 0.0F, 0.0166666675F, 15U, &frac);
  uVarTmp = intrp1d_fu32fl(bpIdx, frac, tableData_c);
  if (negFlag) {
    uVarTmp = -uVarTmp;
  }

  /* End of Trigonometry: '<S1>/SinCos1' */

  /* Trigonometry: '<S1>/SinCos' */
  uVarTmp_0 = yVarTmp;
  if (yVarTmp < 0.0F) {
    uVarTmp_0 = yVarTmp + 1.0F;
  }

  if (uVarTmp_0 > 0.5F) {
    uVarTmp_0 -= 0.5F;
    negFlag = true;
  } else {
    negFlag = false;
  }

  if (uVarTmp_0 > 0.25F) {
    uVarTmp_0 = 0.5F - uVarTmp_0;
  }

  bpIdx = plook_u32ff_evencg(uVarTmp_0, 0.0F, 0.0166666675F, 15U, &frac);
  yVarTmp = intrp1d_fu32fl(bpIdx, frac, tableData_c);
  if (negFlag) {
    yVarTmp = -yVarTmp;
  }

  /* Outputs for Atomic SubSystem: '<S1>/SVPWM' */
  /* Sum: '<S2>/Add' incorporates:
   *  Inport: '<Root>/ud'
   *  Inport: '<Root>/uq'
   *  Inport: '<Root>/v_bus'
   *  Outport: '<Root>/tABC'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product1'
   *  Product: '<S2>/Product2'
   *  Product: '<S2>/Product3'
   *  Sum: '<S2>/Add1'
   */
  SVPWM(rtU.ud * uVarTmp - rtU.uq * yVarTmp, rtU.ud * yVarTmp + rtU.uq * uVarTmp,
        rtU.v_bus, rtY.tABC);

  /* End of Outputs for SubSystem: '<S1>/SVPWM' */

  /* Update for UnitDelay: '<S3>/Unit Delay' */
  rtDW.UnitDelay_DSTATE = rtb_Sum;
}

/* Model step function */
void VF_step(void)
{
  /* Outputs for Atomic SubSystem: '<Root>/VF mode' */
  VFmode();

  /* End of Outputs for SubSystem: '<Root>/VF mode' */
}

/* Model initialize function */
void VF_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
