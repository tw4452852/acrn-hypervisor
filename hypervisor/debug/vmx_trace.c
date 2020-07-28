#include <vcpu.h>
#include <logmsg.h>
#include "vmx_trace.h"

void vmx_trace_toggle(struct acrn_vcpu *vcpu)
{
	uint64_t gva = vcpu_get_gpreg(vcpu, CPU_REG_RDI);
	uint64_t gpa;
	uint32_t err_code;

	if (!vcpu->arch.trace) {
		if(gva2gpa(vcpu, gva, &gpa, &err_code)) {
			pr_err("gva2gpa failed: %#x, %#lx\n", err_code, gva);
			return;
		}
		vcpu->arch.trace_hva = gpa2hva(vcpu->vm, gpa);
	}
	vcpu->arch.trace ^= true;
	pr_err("trace vmx transition: %s\n", vcpu->arch.trace ? "on" : "off");
}

void vmx_trace_add(struct acrn_vcpu *vcpu, enum vmx_trace_stage stage)
{
	if (!vcpu->arch.trace)
		return;

	stac();
	vcpu->arch.trace_hva->ts[stage] = rdtsc();
	if (stage == VMX_TRACE_VMEXIT_HANDLER_PRE) {
		vcpu->arch.trace_hva->reason = vcpu->arch.exit_reason & 0xFFFFUL;
	}
	clac();
}
