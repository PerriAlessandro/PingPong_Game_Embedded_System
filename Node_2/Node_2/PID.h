#define K_I 10
#define K_D 10

uint16_t total_err=0;
uint16_t prev_err=0;
uint16_t T=1;

uint16_t PID_controller(uint16_t curr_pos, uint16_t des_pos){
	uint16_t curr_err=curr_pos-des_pos;
	total_err+=curr_err;

	uint16_t u_i=T*K_I*total_err;
	uint16_t u_d=K_D/T*(curr_err-prev_err);
	prev_err=curr_err;
	uint16_t u=u_i+u_d;
	return u;	

}