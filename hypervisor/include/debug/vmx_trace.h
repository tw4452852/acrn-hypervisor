#ifndef VMX_TRACE_H_INCLUDED
#define VMX_TRACE_H_INCLUDED

enum vmx_trace_stage {
	VMX_TRACE_VMEXIT_HANDLER_PRE,
	VMX_TRACE_VMEXIT_HANDLER_POST,
	VMX_TRACE_VMENTER_PRE,

	VMX_TRACE_NUM_STAGES
};

void vmx_trace_toggle(struct acrn_vcpu *vcpu);
void vmx_trace_add(struct acrn_vcpu *vcpu, enum vmx_trace_stage stage);

#endif // VMX_TRACE_H_INCLUDED

