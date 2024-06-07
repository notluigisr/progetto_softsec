static char *tg3_phy_string(struct tg3 *tp)
{
	switch (tp->phy_id & TG3_PHY_ID_MASK) {
	case TG3_PHY_ID_BCM5400:	return "STR";
	case TG3_PHY_ID_BCM5401:	return "STR";
	case TG3_PHY_ID_BCM5411:	return "STR";
	case TG3_PHY_ID_BCM5701:	return "STR";
	case TG3_PHY_ID_BCM5703:	return "STR";
	case TG3_PHY_ID_BCM5704:	return "STR";
	case TG3_PHY_ID_BCM5705:	return "STR";
	case TG3_PHY_ID_BCM5750:	return "STR";
	case TG3_PHY_ID_BCM5752:	return "STR";
	case TG3_PHY_ID_BCM5714:	return "STR";
	case TG3_PHY_ID_BCM5780:	return "STR";
	case TG3_PHY_ID_BCM5755:	return "STR";
	case TG3_PHY_ID_BCM5787:	return "STR";
	case TG3_PHY_ID_BCM5784:	return "STR";
	case TG3_PHY_ID_BCM5756:	return "STR";
	case TG3_PHY_ID_BCM5906:	return "STR";
	case TG3_PHY_ID_BCM5761:	return "STR";
	case TG3_PHY_ID_BCM5718C:	return "STR";
	case TG3_PHY_ID_BCM5718S:	return "STR";
	case TG3_PHY_ID_BCM57765:	return "STR";
	case TG3_PHY_ID_BCM5719C:	return "STR";
	case TG3_PHY_ID_BCM5720C:	return "STR";
	case TG3_PHY_ID_BCM5762:	return "STR";
	case TG3_PHY_ID_BCM8002:	return "STR";
	case 0:			return "STR";
	default:		return "STR";
	}
}