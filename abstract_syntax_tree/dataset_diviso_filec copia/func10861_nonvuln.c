void dn_fib_select_multipath(const struct flowidn *fld, struct dn_fib_res *res)
{
	struct dn_fib_info *fi = res->fi;
	int w;

	spin_lock_bh(&dn_fib_multipath_lock);
	if (fi->fib_power <= 0) {
		int power = 0;
		change_nexthops(fi) {
			if (!(nh->nh_flags&RTNH_F_DEAD)) {
				power += nh->nh_weight;
				nh->nh_power = nh->nh_weight;
			}
		} endfor_nexthops(fi);
		fi->fib_power = power;
		if (power < 0) {
			spin_unlock_bh(&dn_fib_multipath_lock);
			res->nh_sel = 0;
			return;
		}
	}

	w = jiffies % fi->fib_power;

	change_nexthops(fi) {
		if (!(nh->nh_flags&RTNH_F_DEAD) && nh->nh_power) {
			if ((w -= nh->nh_power) <= 0) {
				nh->nh_power--;
				fi->fib_power--;
				res->nh_sel = nhsel;
				spin_unlock_bh(&dn_fib_multipath_lock);
				return;
			}
		}
	} endfor_nexthops(fi);
	res->nh_sel = 0;
	spin_unlock_bh(&dn_fib_multipath_lock);
}