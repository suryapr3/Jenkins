#ifndef _CIR_BUF_HIVE_H_
#define _CIR_BUF_HIVE_H_

#define INLINE inline
#define IS_PROD 0
#define IS_CONS (1<<16)

#define debug_STATE( x )\
{\
  int temp0,temp1,temp2,temp3,temp4,temp5;\
  OP___printstring( "fu mc_get_state{1,2,3} idx=" );\
  OP___dump(x,x);\
  OP___printstring( "{s1}0 :#request[15] #P/C[1]#in_use[16], 1:tbs[16]ptr[16], 2:message[16],{s2} 3:addres[32], {s3} 4:blocking[1], {sg} 5:value[32]\n" );\
  mc_get_state(Any, 0, x, temp0 );\
  OP___dump(0,temp0);\
  mc_get_state(Any, 1, x, temp1 );\
  OP___dump(1,temp1);\
  mc_get_state(Any, 2, x, temp2 );\
  OP___dump(2,temp2);\
  mc_get_state(Any, 3, x, temp3 );\
  OP___dump(3,temp3);\
  mc_get_state(Any, 4, x, temp4 );\
  OP___dump(4,temp4);\
  mc_get_state(Any, 5, x, temp5 );\
  OP___dump(5,temp5);\
}


 /*****************************************************************************
 *Function: circ_buff_init
 *Description:
 *    - initializes the Functional unit(FU) state for the channel  "sm_ch"
 * Parameters:
 *    ch_type: channel type: consumer or producer
 *    tbs: token buffer size
 *    token_per_request : number of tokens requested in every access of
 *                        mc_claim_debug  and mc_complete_and_cancel instructions
 *    loc_ptr : initial value for local pointer
 * returns: none
 *****************************************************************************/
INLINE void circ_buff_init( int ch_type, int tbs, int token_per_request, int loc_ptr, int sm_ch)
{
    /* mc_init( slot_id, A, C)
    input A = contains three parts
          a1) Token request rate                  bits[31:17]
                number of tokens consumed/produced for each operation of mc_claim_debug and/or mc_complete_and_cancel.
                Mostly set at init time, can be modified later based on run time needs by mc_set_rate operation.
          a2) Producer(0), consumer(1)            bit[16]
          a3) Token buffer size                   bits[15:0]
                a2,a3 cannot be changed without a mc_reset follwed by mc_init
    input C = channel id, each channel id has an attached semaphore.

       mc_init_local_idc( slot_id, B, C)
    input B = init value for loacl pointer
              - write pointer for producer
              - read pointer for consumer
    input C = channel id, each channel id has an attached semaphore.*/

    mc_init( Any, tbs + (token_per_request<<17) + ch_type, sm_ch);
    mc_init_local_idc( Any, loc_ptr, sm_ch);
    debug_STATE(sm_ch);
}
 /*****************************************************************************
 *Function: semaphore_gate_init
 *Description:
 *    - initializes the semaphore_gate state, to be done at core init time
 * Parameters:
 *    loc_ptr_address : address monitorend by semaphore on the local core,
 *               external core updates the pointer and writes to this location
 * returns: none
 *****************************************************************************/
INLINE void semaphore_gate_init()
{
    /*resets all channels of semaphore gate and TSU*/
    mc_reset( Any , 0 );
}
#endif /* _CIR_BUF_HIVE_H_ */
