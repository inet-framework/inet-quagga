#include "globalvars.h"

struct GlobalVars * GlobalVars_createActiveSet()
{
	struct GlobalVars * ptr = (struct GlobalVars *)malloc(sizeof(struct GlobalVars));
	memset(ptr, 0, sizeof(struct GlobalVars));
	return ptr;
}

int* GlobalVars_errno()
{
	return &__activeVars->errno__X;
}

extern struct cmd_element no_rip_redistribute_type_cmd_ripd;
extern struct route_map_rule_cmd route_match_metric_cmd_ripd;
extern struct cmd_element rip_passive_interface_cmd_ripd;
extern struct cmd_element no_ip_rip_send_version_cmd_ripd;
extern struct cmd_element rip_offset_list_ifname_cmd_ripd;
extern struct cmd_element match_ip_address_cmd_ripd;
extern struct cmd_element no_rip_redistribute_type_routemap_cmd_ripd;
extern struct route_map_rule_cmd route_match_ip_next_hop_cmd_ripd;
extern struct cmd_element no_rip_offset_list_ifname_cmd_ripd;
extern struct cmd_element no_debug_rip_zebra_cmd_ripd;
extern struct cmd_element no_rip_route_cmd_ripd;
extern struct cmd_element no_set_metric_val_cmd_ripd;
extern struct cmd_element no_ip_rip_authentication_string_cmd_ripd;
extern struct cmd_element no_rip_network_cmd_ripd;
extern struct cmd_element no_ip_rip_authentication_key_chain2_cmd_ripd;
extern struct cmd_element rip_distance_source_access_list_cmd_ripd;
extern struct cmd_element ip_rip_send_version_2_cmd_ripd;
extern struct cmd_element ip_rip_send_version_cmd_ripd;
extern struct cmd_element no_rip_distance_source_cmd_ripd;
extern struct cmd_element no_router_zebra_cmd_ripd;
extern struct cmd_element debug_rip_packet_cmd_ripd;
extern struct cmd_element match_tag_cmd_ripd;
extern struct cmd_element no_ip_rip_authentication_mode_cmd_ripd;
extern struct cmd_element no_match_ip_address_cmd_ripd;
extern struct cmd_element no_rip_redistribute_type_metric_routemap_cmd_ripd;
extern struct cmd_element no_match_ip_address_prefix_list_val_cmd_ripd;
extern struct cmd_element no_rip_timers_val_cmd_ripd;
extern struct cmd_element ip_rip_authentication_string_cmd_ripd;
extern struct cmd_element set_metric_cmd_ripd;
extern struct cmd_element rip_redistribute_type_metric_cmd_ripd;
extern struct route_map_rule_cmd route_match_ip_address_cmd_ripd;
extern struct cmd_element ip_rip_receive_version_2_cmd_ripd;
extern struct cmd_element rip_redistribute_type_metric_routemap_cmd_ripd;
extern struct route_map_rule_cmd route_set_metric_cmd_ripd;
extern struct cmd_element no_rip_default_metric_cmd_ripd;
extern struct route_map_rule_cmd route_match_ip_next_hop_prefix_list_cmd_ripd;
extern struct cmd_element no_debug_rip_packet_direct_cmd_ripd;
extern struct cmd_element set_tag_cmd_ripd;
extern struct cmd_element no_debug_rip_packet_cmd_ripd;
extern struct cmd_element router_zebra_cmd_ripd;
extern struct cmd_element rip_default_information_originate_cmd_ripd;
extern struct cmd_element no_ip_rip_send_version_num_cmd_ripd;
extern struct cmd_element rip_default_metric_cmd_ripd;
extern struct cmd_element ip_rip_authentication_mode_authlen_cmd_ripd;
extern struct route_map_rule_cmd route_match_tag_cmd_ripd;
extern struct route_map_rule_cmd route_match_interface_cmd_ripd;
extern struct cmd_element debug_rip_events_cmd_ripd;
extern struct cmd_element no_rip_offset_list_cmd_ripd;
extern struct cmd_element no_rip_neighbor_cmd_ripd;
extern struct cmd_element match_ip_next_hop_prefix_list_cmd_ripd;
extern struct cmd_element no_set_tag_val_cmd_ripd;
extern struct cmd_element match_ip_address_prefix_list_cmd_ripd;
extern struct cmd_element no_match_ip_address_val_cmd_ripd;
extern struct cmd_element no_rip_redistribute_rip_cmd_ripd;
extern struct cmd_element no_match_metric_cmd_ripd;
extern struct cmd_element rip_neighbor_cmd_ripd;
extern struct cmd_element set_ip_nexthop_cmd_ripd;
extern struct cmd_element no_rip_default_metric_val_cmd_ripd;
extern struct cmd_element no_router_rip_cmd_ripd;
extern struct cmd_element no_match_ip_next_hop_val_cmd_ripd;
extern struct cmd_element ip_rip_receive_version_1_cmd_ripd;
extern struct route_map_rule_cmd route_set_ip_nexthop_cmd_ripd;
extern struct cmd_element no_rip_distance_cmd_ripd;
extern struct cmd_element rip_redistribute_type_cmd_ripd;
extern struct cmd_element no_ip_rip_split_horizon_cmd_ripd;
extern struct cmd_element rip_redistribute_rip_cmd_ripd;
extern struct cmd_element no_match_interface_val_cmd_ripd;
extern struct route_map_rule_cmd route_match_ip_address_prefix_list_cmd_ripd;
extern struct cmd_element no_ip_rip_authentication_key_chain_cmd_ripd;
extern struct cmd_element no_rip_version_val_cmd_ripd;
extern struct cmd_element rip_network_cmd_ripd;
extern struct cmd_element debug_rip_zebra_cmd_ripd;
extern struct cmd_element debug_rip_packet_direct_cmd_ripd;
extern struct cmd_element no_match_metric_val_cmd_ripd;
extern struct cmd_element router_rip_cmd_ripd;
extern struct cmd_element no_ip_rip_authentication_string2_cmd_ripd;
extern struct cmd_element no_rip_passive_interface_cmd_ripd;
extern struct cmd_element no_rip_version_cmd_ripd;
extern struct cmd_element no_set_metric_cmd_ripd;
extern struct cmd_element no_match_interface_cmd_ripd;
extern struct cmd_element no_debug_rip_events_cmd_ripd;
extern struct cmd_element match_interface_cmd_ripd;
extern struct cmd_element ip_rip_split_horizon_poisoned_reverse_cmd_ripd;
extern struct cmd_element ip_rip_send_version_1_cmd_ripd;
extern struct cmd_element no_match_tag_val_cmd_ripd;
extern struct cmd_element rip_offset_list_cmd_ripd;
extern struct cmd_element no_match_ip_next_hop_cmd_ripd;
extern struct cmd_element no_rip_distance_source_access_list_cmd_ripd;
extern struct cmd_element set_metric_addsub_cmd_ripd;
extern struct route_map_rule_cmd route_set_tag_cmd_ripd;
extern struct cmd_element no_match_ip_next_hop_prefix_list_val_cmd_ripd;
extern struct cmd_element match_ip_next_hop_cmd_ripd;
extern struct cmd_element no_set_tag_cmd_ripd;
extern struct cmd_element no_match_ip_next_hop_prefix_list_cmd_ripd;
extern struct cmd_element no_rip_default_information_originate_cmd_ripd;
extern struct cmd_element show_ip_rip_cmd_ripd;
extern struct cmd_element ip_rip_authentication_key_chain_cmd_ripd;
extern struct cmd_element rip_distance_cmd_ripd;
extern struct cmd_element no_match_ip_address_prefix_list_cmd_ripd;
extern struct cmd_element no_set_ip_nexthop_cmd_ripd;
extern struct cmd_element no_ip_rip_receive_version_cmd_ripd;
extern struct cmd_element rip_distance_source_cmd_ripd;
extern struct cmd_element ip_rip_receive_version_cmd_ripd;
extern struct cmd_element no_match_tag_cmd_ripd;
extern struct cmd_element rip_version_cmd_ripd;
extern struct cmd_element no_ip_rip_split_horizon_poisoned_reverse_cmd_ripd;
extern struct cmd_element no_ip_rip_authentication_mode_type_authlen_cmd_ripd;
extern struct cmd_element no_ip_rip_authentication_mode_type_cmd_ripd;
extern struct cmd_element ip_rip_authentication_mode_cmd_ripd;
extern struct cmd_element no_rip_timers_cmd_ripd;
extern struct cmd_element rip_route_cmd_ripd;
extern struct cmd_element show_debugging_rip_cmd_ripd;
extern struct cmd_element match_metric_cmd_ripd;
extern struct cmd_element rip_timers_cmd_ripd;
extern struct cmd_element no_rip_redistribute_type_metric_cmd_ripd;
extern struct cmd_element no_ip_rip_receive_version_num_cmd_ripd;
extern struct cmd_element no_set_ip_nexthop_val_cmd_ripd;
extern struct cmd_element rip_redistribute_type_routemap_cmd_ripd;
extern struct cmd_element show_ip_rip_status_cmd_ripd;
extern struct cmd_element ip_rip_split_horizon_cmd_ripd;
extern struct cmd_element debug_rip_packet_detail_cmd_ripd;

void GlobalVars_initializeActiveSet_ripd()
{
	struct cmd_node zebra_node__T = 
{
  ZEBRA_NODE,
  "%s(config-router)# ",
};
	struct cmd_node rip_node__T = 
{
  RIP_NODE,
  "%s(config-router)# ",
  1
};
	struct cmd_node debug_node__T = 
{
  DEBUG_NODE,
  "",				
  1
};
	struct cmd_node interface_node__T = 
{
  INTERFACE_NODE,
  "%s(config-if)# ",
  1,
};
	memcpy(&__activeVars->no_rip_redistribute_type_cmd__X, &no_rip_redistribute_type_cmd_ripd, sizeof(no_rip_redistribute_type_cmd_ripd));
	memcpy(&__activeVars->route_match_metric_cmd__X, &route_match_metric_cmd_ripd, sizeof(route_match_metric_cmd_ripd));
	memcpy(&__activeVars->rip_passive_interface_cmd__X, &rip_passive_interface_cmd_ripd, sizeof(rip_passive_interface_cmd_ripd));
	memcpy(&__activeVars->no_ip_rip_send_version_cmd__X, &no_ip_rip_send_version_cmd_ripd, sizeof(no_ip_rip_send_version_cmd_ripd));
	__activeVars->retain_mode__X =  0;
	memcpy(&__activeVars->rip_offset_list_ifname_cmd__X, &rip_offset_list_ifname_cmd_ripd, sizeof(rip_offset_list_ifname_cmd_ripd));
	memcpy(&__activeVars->match_ip_address_cmd__X, &match_ip_address_cmd_ripd, sizeof(match_ip_address_cmd_ripd));
	memcpy(&__activeVars->no_rip_redistribute_type_routemap_cmd__X, &no_rip_redistribute_type_routemap_cmd_ripd, sizeof(no_rip_redistribute_type_routemap_cmd_ripd));
	memcpy(&__activeVars->route_match_ip_next_hop_cmd__X, &route_match_ip_next_hop_cmd_ripd, sizeof(route_match_ip_next_hop_cmd_ripd));
	__activeVars->pid_file__X =  PATH_RIPD_PID;
	memcpy(&__activeVars->no_rip_offset_list_ifname_cmd__X, &no_rip_offset_list_ifname_cmd_ripd, sizeof(no_rip_offset_list_ifname_cmd_ripd));
	memcpy(&__activeVars->no_debug_rip_zebra_cmd__X, &no_debug_rip_zebra_cmd_ripd, sizeof(no_debug_rip_zebra_cmd_ripd));
	memcpy(&__activeVars->no_rip_route_cmd__X, &no_rip_route_cmd_ripd, sizeof(no_rip_route_cmd_ripd));
	memcpy(&__activeVars->no_set_metric_val_cmd__X, &no_set_metric_val_cmd_ripd, sizeof(no_set_metric_val_cmd_ripd));
	memcpy(&__activeVars->no_ip_rip_authentication_string_cmd__X, &no_ip_rip_authentication_string_cmd_ripd, sizeof(no_ip_rip_authentication_string_cmd_ripd));
	memcpy(&__activeVars->no_rip_network_cmd__X, &no_rip_network_cmd_ripd, sizeof(no_rip_network_cmd_ripd));
	memcpy(&__activeVars->no_ip_rip_authentication_key_chain2_cmd__X, &no_ip_rip_authentication_key_chain2_cmd_ripd, sizeof(no_ip_rip_authentication_key_chain2_cmd_ripd));
	memcpy(&__activeVars->rip_distance_source_access_list_cmd__X, &rip_distance_source_access_list_cmd_ripd, sizeof(rip_distance_source_access_list_cmd_ripd));
	memcpy(&__activeVars->ip_rip_send_version_2_cmd__X, &ip_rip_send_version_2_cmd_ripd, sizeof(ip_rip_send_version_2_cmd_ripd));
	memcpy(&__activeVars->ip_rip_send_version_cmd__X, &ip_rip_send_version_cmd_ripd, sizeof(ip_rip_send_version_cmd_ripd));
	memcpy(&__activeVars->no_rip_distance_source_cmd__X, &no_rip_distance_source_cmd_ripd, sizeof(no_rip_distance_source_cmd_ripd));
	memcpy(&__activeVars->no_router_zebra_cmd__X, &no_router_zebra_cmd_ripd, sizeof(no_router_zebra_cmd_ripd));
	memcpy(&__activeVars->debug_rip_packet_cmd__X, &debug_rip_packet_cmd_ripd, sizeof(debug_rip_packet_cmd_ripd));
	memcpy(&__activeVars->match_tag_cmd__X, &match_tag_cmd_ripd, sizeof(match_tag_cmd_ripd));
	__activeVars->rip_global_route_changes__X =  0;
	__activeVars->vty_addr__X =  NULL;
	memcpy(&__activeVars->no_ip_rip_authentication_mode_cmd__X, &no_ip_rip_authentication_mode_cmd_ripd, sizeof(no_ip_rip_authentication_mode_cmd_ripd));
	memcpy(&__activeVars->no_match_ip_address_cmd__X, &no_match_ip_address_cmd_ripd, sizeof(no_match_ip_address_cmd_ripd));
	memcpy(&__activeVars->no_rip_redistribute_type_metric_routemap_cmd__X, &no_rip_redistribute_type_metric_routemap_cmd_ripd, sizeof(no_rip_redistribute_type_metric_routemap_cmd_ripd));
	memcpy(&__activeVars->no_match_ip_address_prefix_list_val_cmd__X, &no_match_ip_address_prefix_list_val_cmd_ripd, sizeof(no_match_ip_address_prefix_list_val_cmd_ripd));
	memcpy(&__activeVars->zebra_node__X, &zebra_node__T, sizeof(zebra_node__T));
	memcpy(&__activeVars->no_rip_timers_val_cmd__X, &no_rip_timers_val_cmd_ripd, sizeof(no_rip_timers_val_cmd_ripd));
	memcpy(&__activeVars->ip_rip_authentication_string_cmd__X, &ip_rip_authentication_string_cmd_ripd, sizeof(ip_rip_authentication_string_cmd_ripd));
	memcpy(&__activeVars->set_metric_cmd__X, &set_metric_cmd_ripd, sizeof(set_metric_cmd_ripd));
	memcpy(&__activeVars->rip_redistribute_type_metric_cmd__X, &rip_redistribute_type_metric_cmd_ripd, sizeof(rip_redistribute_type_metric_cmd_ripd));
	memcpy(&__activeVars->route_match_ip_address_cmd__X, &route_match_ip_address_cmd_ripd, sizeof(route_match_ip_address_cmd_ripd));
	memcpy(&__activeVars->ip_rip_receive_version_2_cmd__X, &ip_rip_receive_version_2_cmd_ripd, sizeof(ip_rip_receive_version_2_cmd_ripd));
	memcpy(&__activeVars->rip_redistribute_type_metric_routemap_cmd__X, &rip_redistribute_type_metric_routemap_cmd_ripd, sizeof(rip_redistribute_type_metric_routemap_cmd_ripd));
	memcpy(&__activeVars->route_set_metric_cmd__X, &route_set_metric_cmd_ripd, sizeof(route_set_metric_cmd_ripd));
	memcpy(&__activeVars->no_rip_default_metric_cmd__X, &no_rip_default_metric_cmd_ripd, sizeof(no_rip_default_metric_cmd_ripd));
	memcpy(&__activeVars->route_match_ip_next_hop_prefix_list_cmd__X, &route_match_ip_next_hop_prefix_list_cmd_ripd, sizeof(route_match_ip_next_hop_prefix_list_cmd_ripd));
	memcpy(&__activeVars->no_debug_rip_packet_direct_cmd__X, &no_debug_rip_packet_direct_cmd_ripd, sizeof(no_debug_rip_packet_direct_cmd_ripd));
	memcpy(&__activeVars->set_tag_cmd__X, &set_tag_cmd_ripd, sizeof(set_tag_cmd_ripd));
	memcpy(&__activeVars->no_debug_rip_packet_cmd__X, &no_debug_rip_packet_cmd_ripd, sizeof(no_debug_rip_packet_cmd_ripd));
	memcpy(&__activeVars->router_zebra_cmd__X, &router_zebra_cmd_ripd, sizeof(router_zebra_cmd_ripd));
	memcpy(&__activeVars->rip_default_information_originate_cmd__X, &rip_default_information_originate_cmd_ripd, sizeof(rip_default_information_originate_cmd_ripd));
	memcpy(&__activeVars->no_ip_rip_send_version_num_cmd__X, &no_ip_rip_send_version_num_cmd_ripd, sizeof(no_ip_rip_send_version_num_cmd_ripd));
	memcpy(&__activeVars->rip_default_metric_cmd__X, &rip_default_metric_cmd_ripd, sizeof(rip_default_metric_cmd_ripd));
	memcpy(&__activeVars->ip_rip_authentication_mode_authlen_cmd__X, &ip_rip_authentication_mode_authlen_cmd_ripd, sizeof(ip_rip_authentication_mode_authlen_cmd_ripd));
	__activeVars->rip__X =  NULL;
	memcpy(&__activeVars->route_match_tag_cmd__X, &route_match_tag_cmd_ripd, sizeof(route_match_tag_cmd_ripd));
	memcpy(&__activeVars->route_match_interface_cmd__X, &route_match_interface_cmd_ripd, sizeof(route_match_interface_cmd_ripd));
	__activeVars->rip_global_queries__X =  0;
	memcpy(&__activeVars->debug_rip_events_cmd__X, &debug_rip_events_cmd_ripd, sizeof(debug_rip_events_cmd_ripd));
	memcpy(&__activeVars->no_rip_offset_list_cmd__X, &no_rip_offset_list_cmd_ripd, sizeof(no_rip_offset_list_cmd_ripd));
	memcpy(&__activeVars->no_rip_neighbor_cmd__X, &no_rip_neighbor_cmd_ripd, sizeof(no_rip_neighbor_cmd_ripd));
	memcpy(&__activeVars->match_ip_next_hop_prefix_list_cmd__X, &match_ip_next_hop_prefix_list_cmd_ripd, sizeof(match_ip_next_hop_prefix_list_cmd_ripd));
	memcpy(&__activeVars->no_set_tag_val_cmd__X, &no_set_tag_val_cmd_ripd, sizeof(no_set_tag_val_cmd_ripd));
	memcpy(&__activeVars->match_ip_address_prefix_list_cmd__X, &match_ip_address_prefix_list_cmd_ripd, sizeof(match_ip_address_prefix_list_cmd_ripd));
	memcpy(&__activeVars->no_match_ip_address_val_cmd__X, &no_match_ip_address_val_cmd_ripd, sizeof(no_match_ip_address_val_cmd_ripd));
	__activeVars->config_file__X =  NULL;
	memcpy(&__activeVars->no_rip_redistribute_rip_cmd__X, &no_rip_redistribute_rip_cmd_ripd, sizeof(no_rip_redistribute_rip_cmd_ripd));
	memcpy(&__activeVars->no_match_metric_cmd__X, &no_match_metric_cmd_ripd, sizeof(no_match_metric_cmd_ripd));
	memcpy(&__activeVars->rip_neighbor_cmd__X, &rip_neighbor_cmd_ripd, sizeof(rip_neighbor_cmd_ripd));
	memcpy(&__activeVars->set_ip_nexthop_cmd__X, &set_ip_nexthop_cmd_ripd, sizeof(set_ip_nexthop_cmd_ripd));
	memcpy(&__activeVars->no_rip_default_metric_val_cmd__X, &no_rip_default_metric_val_cmd_ripd, sizeof(no_rip_default_metric_val_cmd_ripd));
	memcpy(&__activeVars->no_router_rip_cmd__X, &no_router_rip_cmd_ripd, sizeof(no_router_rip_cmd_ripd));
	memcpy(&__activeVars->no_match_ip_next_hop_val_cmd__X, &no_match_ip_next_hop_val_cmd_ripd, sizeof(no_match_ip_next_hop_val_cmd_ripd));
	memcpy(&__activeVars->ip_rip_receive_version_1_cmd__X, &ip_rip_receive_version_1_cmd_ripd, sizeof(ip_rip_receive_version_1_cmd_ripd));
	memcpy(&__activeVars->route_set_ip_nexthop_cmd__X, &route_set_ip_nexthop_cmd_ripd, sizeof(route_set_ip_nexthop_cmd_ripd));
	memcpy(&__activeVars->no_rip_distance_cmd__X, &no_rip_distance_cmd_ripd, sizeof(no_rip_distance_cmd_ripd));
	__activeVars->rip_debug_packet__X =  0;
	memcpy(&__activeVars->rip_redistribute_type_cmd__X, &rip_redistribute_type_cmd_ripd, sizeof(rip_redistribute_type_cmd_ripd));
	memcpy(&__activeVars->no_ip_rip_split_horizon_cmd__X, &no_ip_rip_split_horizon_cmd_ripd, sizeof(no_ip_rip_split_horizon_cmd_ripd));
	memcpy(&__activeVars->rip_redistribute_rip_cmd__X, &rip_redistribute_rip_cmd_ripd, sizeof(rip_redistribute_rip_cmd_ripd));
	memcpy(&__activeVars->no_match_interface_val_cmd__X, &no_match_interface_val_cmd_ripd, sizeof(no_match_interface_val_cmd_ripd));
	memcpy(&__activeVars->rip_node__X, &rip_node__T, sizeof(rip_node__T));
	memcpy(&__activeVars->route_match_ip_address_prefix_list_cmd__X, &route_match_ip_address_prefix_list_cmd_ripd, sizeof(route_match_ip_address_prefix_list_cmd_ripd));
	memcpy(&__activeVars->no_ip_rip_authentication_key_chain_cmd__X, &no_ip_rip_authentication_key_chain_cmd_ripd, sizeof(no_ip_rip_authentication_key_chain_cmd_ripd));
	memcpy(&__activeVars->no_rip_version_val_cmd__X, &no_rip_version_val_cmd_ripd, sizeof(no_rip_version_val_cmd_ripd));
	memcpy(&__activeVars->rip_network_cmd__X, &rip_network_cmd_ripd, sizeof(rip_network_cmd_ripd));
	memcpy(&__activeVars->debug_rip_zebra_cmd__X, &debug_rip_zebra_cmd_ripd, sizeof(debug_rip_zebra_cmd_ripd));
	memcpy(&__activeVars->debug_rip_packet_direct_cmd__X, &debug_rip_packet_direct_cmd_ripd, sizeof(debug_rip_packet_direct_cmd_ripd));
	memcpy(&__activeVars->no_match_metric_val_cmd__X, &no_match_metric_val_cmd_ripd, sizeof(no_match_metric_val_cmd_ripd));
	memcpy(&__activeVars->router_rip_cmd__X, &router_rip_cmd_ripd, sizeof(router_rip_cmd_ripd));
	memcpy(&__activeVars->no_ip_rip_authentication_string2_cmd__X, &no_ip_rip_authentication_string2_cmd_ripd, sizeof(no_ip_rip_authentication_string2_cmd_ripd));
	memcpy(&__activeVars->no_rip_passive_interface_cmd__X, &no_rip_passive_interface_cmd_ripd, sizeof(no_rip_passive_interface_cmd_ripd));
	memcpy(&__activeVars->no_rip_version_cmd__X, &no_rip_version_cmd_ripd, sizeof(no_rip_version_cmd_ripd));
	memcpy(&__activeVars->no_set_metric_cmd__X, &no_set_metric_cmd_ripd, sizeof(no_set_metric_cmd_ripd));
	memcpy(&__activeVars->no_match_interface_cmd__X, &no_match_interface_cmd_ripd, sizeof(no_match_interface_cmd_ripd));
	memcpy(&__activeVars->no_debug_rip_events_cmd__X, &no_debug_rip_events_cmd_ripd, sizeof(no_debug_rip_events_cmd_ripd));
	memcpy(&__activeVars->match_interface_cmd__X, &match_interface_cmd_ripd, sizeof(match_interface_cmd_ripd));
	memcpy(&__activeVars->ip_rip_split_horizon_poisoned_reverse_cmd__X, &ip_rip_split_horizon_poisoned_reverse_cmd_ripd, sizeof(ip_rip_split_horizon_poisoned_reverse_cmd_ripd));
	__activeVars->rip_debug_zebra__X =  0;
	__activeVars->vty_port__X =  RIP_VTY_PORT;
	__activeVars->zclient__X =  NULL;
	memcpy(&__activeVars->ip_rip_send_version_1_cmd__X, &ip_rip_send_version_1_cmd_ripd, sizeof(ip_rip_send_version_1_cmd_ripd));
	memcpy(&__activeVars->debug_node__X, &debug_node__T, sizeof(debug_node__T));
	memcpy(&__activeVars->no_match_tag_val_cmd__X, &no_match_tag_val_cmd_ripd, sizeof(no_match_tag_val_cmd_ripd));
	memcpy(&__activeVars->rip_offset_list_cmd__X, &rip_offset_list_cmd_ripd, sizeof(rip_offset_list_cmd_ripd));
	memcpy(&__activeVars->no_match_ip_next_hop_cmd__X, &no_match_ip_next_hop_cmd_ripd, sizeof(no_match_ip_next_hop_cmd_ripd));
	memcpy(&__activeVars->no_rip_distance_source_access_list_cmd__X, &no_rip_distance_source_access_list_cmd_ripd, sizeof(no_rip_distance_source_access_list_cmd_ripd));
	memcpy(&__activeVars->set_metric_addsub_cmd__X, &set_metric_addsub_cmd_ripd, sizeof(set_metric_addsub_cmd_ripd));
	memcpy(&__activeVars->route_set_tag_cmd__X, &route_set_tag_cmd_ripd, sizeof(route_set_tag_cmd_ripd));
	memcpy(&__activeVars->no_match_ip_next_hop_prefix_list_val_cmd__X, &no_match_ip_next_hop_prefix_list_val_cmd_ripd, sizeof(no_match_ip_next_hop_prefix_list_val_cmd_ripd));
	memcpy(&__activeVars->match_ip_next_hop_cmd__X, &match_ip_next_hop_cmd_ripd, sizeof(match_ip_next_hop_cmd_ripd));
	memcpy(&__activeVars->no_set_tag_cmd__X, &no_set_tag_cmd_ripd, sizeof(no_set_tag_cmd_ripd));
	memcpy(&__activeVars->no_match_ip_next_hop_prefix_list_cmd__X, &no_match_ip_next_hop_prefix_list_cmd_ripd, sizeof(no_match_ip_next_hop_prefix_list_cmd_ripd));
	memcpy(&__activeVars->no_rip_default_information_originate_cmd__X, &no_rip_default_information_originate_cmd_ripd, sizeof(no_rip_default_information_originate_cmd_ripd));
	memcpy(&__activeVars->show_ip_rip_cmd__X, &show_ip_rip_cmd_ripd, sizeof(show_ip_rip_cmd_ripd));
	memcpy(&__activeVars->ip_rip_authentication_key_chain_cmd__X, &ip_rip_authentication_key_chain_cmd_ripd, sizeof(ip_rip_authentication_key_chain_cmd_ripd));
	memcpy(&__activeVars->rip_distance_cmd__X, &rip_distance_cmd_ripd, sizeof(rip_distance_cmd_ripd));
	memcpy(&__activeVars->no_match_ip_address_prefix_list_cmd__X, &no_match_ip_address_prefix_list_cmd_ripd, sizeof(no_match_ip_address_prefix_list_cmd_ripd));
	memcpy(&__activeVars->no_set_ip_nexthop_cmd__X, &no_set_ip_nexthop_cmd_ripd, sizeof(no_set_ip_nexthop_cmd_ripd));
	memcpy(&__activeVars->no_ip_rip_receive_version_cmd__X, &no_ip_rip_receive_version_cmd_ripd, sizeof(no_ip_rip_receive_version_cmd_ripd));
	memcpy(&__activeVars->rip_distance_source_cmd__X, &rip_distance_source_cmd_ripd, sizeof(rip_distance_source_cmd_ripd));
	memcpy(&__activeVars->ip_rip_receive_version_cmd__X, &ip_rip_receive_version_cmd_ripd, sizeof(ip_rip_receive_version_cmd_ripd));
	memcpy(&__activeVars->no_match_tag_cmd__X, &no_match_tag_cmd_ripd, sizeof(no_match_tag_cmd_ripd));
	memcpy(&__activeVars->rip_version_cmd__X, &rip_version_cmd_ripd, sizeof(rip_version_cmd_ripd));
	memcpy(&__activeVars->interface_node__X, &interface_node__T, sizeof(interface_node__T));
	memcpy(&__activeVars->no_ip_rip_split_horizon_poisoned_reverse_cmd__X, &no_ip_rip_split_horizon_poisoned_reverse_cmd_ripd, sizeof(no_ip_rip_split_horizon_poisoned_reverse_cmd_ripd));
	memcpy(&__activeVars->no_ip_rip_authentication_mode_type_authlen_cmd__X, &no_ip_rip_authentication_mode_type_authlen_cmd_ripd, sizeof(no_ip_rip_authentication_mode_type_authlen_cmd_ripd));
	memcpy(&__activeVars->no_ip_rip_authentication_mode_type_cmd__X, &no_ip_rip_authentication_mode_type_cmd_ripd, sizeof(no_ip_rip_authentication_mode_type_cmd_ripd));
	memcpy(&__activeVars->ip_rip_authentication_mode_cmd__X, &ip_rip_authentication_mode_cmd_ripd, sizeof(ip_rip_authentication_mode_cmd_ripd));
	memcpy(&__activeVars->no_rip_timers_cmd__X, &no_rip_timers_cmd_ripd, sizeof(no_rip_timers_cmd_ripd));
	memcpy(&__activeVars->rip_route_cmd__X, &rip_route_cmd_ripd, sizeof(rip_route_cmd_ripd));
	memcpy(&__activeVars->show_debugging_rip_cmd__X, &show_debugging_rip_cmd_ripd, sizeof(show_debugging_rip_cmd_ripd));
	memcpy(&__activeVars->match_metric_cmd__X, &match_metric_cmd_ripd, sizeof(match_metric_cmd_ripd));
	memcpy(&__activeVars->rip_timers_cmd__X, &rip_timers_cmd_ripd, sizeof(rip_timers_cmd_ripd));
	memcpy(&__activeVars->no_rip_redistribute_type_metric_cmd__X, &no_rip_redistribute_type_metric_cmd_ripd, sizeof(no_rip_redistribute_type_metric_cmd_ripd));
	memcpy(&__activeVars->no_ip_rip_receive_version_num_cmd__X, &no_ip_rip_receive_version_num_cmd_ripd, sizeof(no_ip_rip_receive_version_num_cmd_ripd));
	memcpy(&__activeVars->no_set_ip_nexthop_val_cmd__X, &no_set_ip_nexthop_val_cmd_ripd, sizeof(no_set_ip_nexthop_val_cmd_ripd));
	memcpy(&__activeVars->rip_redistribute_type_routemap_cmd__X, &rip_redistribute_type_routemap_cmd_ripd, sizeof(rip_redistribute_type_routemap_cmd_ripd));
	memcpy(&__activeVars->show_ip_rip_status_cmd__X, &show_ip_rip_status_cmd_ripd, sizeof(show_ip_rip_status_cmd_ripd));
	memcpy(&__activeVars->ip_rip_split_horizon_cmd__X, &ip_rip_split_horizon_cmd_ripd, sizeof(ip_rip_split_horizon_cmd_ripd));
	__activeVars->rip_debug_event__X =  0;
	memcpy(&__activeVars->debug_rip_packet_detail_cmd__X, &debug_rip_packet_detail_cmd_ripd, sizeof(debug_rip_packet_detail_cmd_ripd));
}

extern struct cmd_element show_ip_ospf_route_cmd_ospfd;
extern struct cmd_element ospf_area_vlink_param1_cmd_ospfd;
extern struct cmd_element no_ospf_area_vlink_param1_cmd_ospfd;
extern struct cmd_element ospf_area_export_list_cmd_ospfd;
extern struct cmd_element ospf_max_metric_router_lsa_shutdown_cmd_ospfd;
extern struct cmd_element no_debug_ospf_zebra_sub_cmd_ospfd;
extern struct cmd_element ospf_area_authentication_cmd_ospfd;
extern struct cmd_element ip_ospf_dead_interval_minimal_cmd_ospfd;
extern struct cmd_element ospf_passive_interface_addr_cmd_ospfd;
extern struct cmd_element no_ip_ospf_retransmit_interval_addr_cmd_ospfd;
extern struct cmd_element show_ip_ospf_neighbor_int_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_external_inter_intra_cmd_ospfd;
extern struct cmd_element router_ospf_id_cmd_ospfd;
extern struct cmd_element ip_ospf_hello_interval_addr_cmd_ospfd;
extern struct cmd_element no_ospf_area_vlink_param4_cmd_ospfd;
extern struct cmd_element ospf_area_range_advertise_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_metric_type_cmd_ospfd;
extern struct cmd_element no_ip_ospf_mtu_ignore_addr_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_type_metric_cmd_ospfd;
extern struct cmd_element router_ospf_cmd_ospfd;
extern struct cmd_element ospf_transmit_delay_cmd_ospfd;
extern struct cmd_element no_ospf_area_default_cost_cmd_ospfd;
extern struct cmd_element ospf_area_range_substitute_cmd_ospfd;
extern struct cmd_element set_metric_type_cmd_ospfd;
extern struct cmd_element no_match_ip_address_prefix_list_val_cmd_ospfd;
extern struct cmd_element no_ip_ospf_transmit_delay_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_type_cmd_ospfd;
extern struct cmd_element ospf_authentication_key_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_intra_inter_cmd_ospfd;
extern struct cmd_element no_debug_ospf_packet_all_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_intra_external_cmd_ospfd;
extern struct cmd_element ospf_passive_interface_default_cmd_ospfd;
extern struct cmd_element set_metric_cmd_ospfd;
extern struct cmd_element debug_ospf_nsm_sub_cmd_ospfd;
extern struct cmd_element ip_ospf_dead_interval_addr_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_type_routemap_cmd_ospfd;
extern struct cmd_element ip_ospf_network_cmd_ospfd;
extern struct cmd_element ospf_area_filter_list_cmd_ospfd;
extern struct route_map_rule_cmd route_set_metric_cmd_ospfd;
extern struct cmd_element ospf_area_vlink_authtype_md5_cmd_ospfd;
extern struct cmd_element ospf_area_nssa_translate_no_summary_cmd_ospfd;
extern struct cmd_element no_ip_ospf_priority_addr_cmd_ospfd;
extern struct cmd_element no_ospf_log_adjacency_changes_detail_cmd_ospfd;
extern struct cmd_element no_ospf_network_area_cmd_ospfd;
extern struct cmd_element no_ospf_max_metric_router_lsa_admin_cmd_ospfd;
extern struct cmd_element ospf_default_metric_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_intra_external_inter_cmd_ospfd;
extern struct cmd_element no_debug_ospf_ism_cmd_ospfd;
extern struct cmd_element no_ospf_neighbor_poll_interval_cmd_ospfd;
extern struct cmd_element no_ospf_area_vlink_cmd_ospfd;
extern struct cmd_element ip_ospf_mtu_ignore_cmd_ospfd;
extern struct route_map_rule_cmd route_match_interface_cmd_ospfd;
extern struct cmd_element ip_ospf_dead_interval_minimal_addr_cmd_ospfd;
extern struct cmd_element no_ospf_area_authentication_cmd_ospfd;
extern struct cmd_element no_ospf_area_range_advertise_cost_cmd_ospfd;
extern struct cmd_element no_ospf_redistribute_source_cmd_ospfd;
extern struct cmd_element ospf_network_cmd_ospfd;
extern struct cmd_element ospf_redistribute_source_type_routemap_cmd_ospfd;
extern struct cmd_element no_ospf_refresh_timer_val_cmd_ospfd;
extern struct cmd_element no_match_ip_address_val_cmd_ospfd;
extern struct cmd_element debug_ospf_zebra_cmd_ospfd;
extern struct cmd_element no_ospf_distance_source_cmd_ospfd;
extern struct cmd_element no_ospf_passive_interface_cmd_ospfd;
extern struct cmd_element ospf_area_default_cost_cmd_ospfd;
extern struct cmd_element no_ospf_distance_cmd_ospfd;
extern struct cmd_element ip_ospf_retransmit_interval_addr_cmd_ospfd;
extern struct cmd_element show_ip_ospf_neighbor_detail_cmd_ospfd;
extern struct cmd_element no_ip_ospf_message_digest_key_cmd_ospfd;
extern struct cmd_element no_ospf_area_nssa_cmd_ospfd;
extern struct cmd_element no_ospf_area_vlink_authtype_md5_cmd_ospfd;
extern struct cmd_element no_router_ospf_cmd_ospfd;
extern struct cmd_element ip_ospf_transmit_delay_cmd_ospfd;
extern struct cmd_element no_ospf_cost_cmd_ospfd;
extern struct cmd_element debug_ospf_nssa_cmd_ospfd;
extern struct cmd_element no_match_interface_val_cmd_ospfd;
extern struct route_map_rule_cmd route_match_ip_address_prefix_list_cmd_ospfd;
extern struct cmd_element debug_ospf_event_cmd_ospfd;
extern struct cmd_element no_ip_ospf_hello_interval_addr_cmd_ospfd;
extern struct cmd_element ospf_log_adjacency_changes_detail_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_metric_type_routemap_cmd_ospfd;
extern struct cmd_element ospf_distance_source_access_list_cmd_ospfd;
extern struct cmd_element show_ip_ospf_database_cmd_ospfd;
extern struct cmd_element no_ospf_hello_interval_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_inter_cmd_ospfd;
extern struct cmd_element ospf_redistribute_source_metric_routemap_cmd_ospfd;
extern struct cmd_element ospf_router_id_cmd_ospfd;
extern struct cmd_element ospf_area_authentication_message_digest_cmd_ospfd;
extern struct cmd_element no_set_metric_cmd_ospfd;
extern struct cmd_element no_match_interface_cmd_ospfd;
extern struct cmd_element no_debug_ospf_packet_send_recv_detail_cmd_ospfd;
extern struct cmd_element no_set_metric_type_val_cmd_ospfd;
extern struct cmd_element debug_ospf_ism_sub_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_inter_external_intra_cmd_ospfd;
extern struct cmd_element ospf_area_range_cmd_ospfd;
extern struct cmd_element ospf_max_metric_router_lsa_admin_cmd_ospfd;
extern struct cmd_element no_ospf_transmit_delay_cmd_ospfd;
extern struct cmd_element ip_ospf_retransmit_interval_cmd_ospfd;
extern struct cmd_element show_ip_ospf_database_type_id_self_cmd_ospfd;
extern struct cmd_element no_ospf_max_metric_router_lsa_startup_cmd_ospfd;
extern struct cmd_element no_ospf_auto_cost_reference_bandwidth_cmd_ospfd;
extern struct cmd_element ospf_area_nssa_no_summary_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_routemap_cmd_ospfd;
extern struct cmd_element ospf_redistribute_source_type_metric_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_external_cmd_ospfd;
extern struct cmd_element no_ospf_message_digest_key_cmd_ospfd;
extern struct cmd_element ospf_log_adjacency_changes_cmd_ospfd;
extern struct cmd_element ospf_message_digest_key_cmd_ospfd;
extern struct cmd_element ospf_redistribute_source_metric_cmd_ospfd;
extern struct cmd_element ip_ospf_authentication_key_cmd_ospfd;
extern struct cmd_element no_ospf_neighbor_priority_pollinterval_cmd_ospfd;
extern struct route_map_rule_cmd route_set_metric_type_cmd_ospfd;
extern struct cmd_element no_ospf_dead_interval_cmd_ospfd;
extern struct cmd_element no_ospf_log_adjacency_changes_cmd_ospfd;
extern struct cmd_element ip_ospf_authentication_cmd_ospfd;
extern struct cmd_element ospf_neighbor_priority_cmd_ospfd;
extern struct cmd_element no_ospf_abr_type_cmd_ospfd;
extern struct cmd_element show_ip_ospf_database_type_self_cmd_ospfd;
extern struct cmd_element show_ip_ospf_database_type_cmd_ospfd;
extern struct cmd_element no_match_ip_next_hop_prefix_list_val_cmd_ospfd;
extern struct cmd_element ospf_area_vlink_authtype_args_authkey_cmd_ospfd;
extern struct cmd_element no_ospf_default_metric_val_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_always_metric_type_routemap_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_always_routemap_cmd_ospfd;
extern struct cmd_element ospf_area_vlink_param2_cmd_ospfd;
extern struct cmd_element no_ospf_neighbor_priority_cmd_ospfd;
extern struct cmd_element no_match_ip_nexthop_val_cmd_ospfd;
extern struct cmd_element show_debugging_ospf_cmd_ospfd;
extern struct cmd_element ospf_area_nssa_cmd_ospfd;
extern struct cmd_element no_debug_ospf_ism_sub_cmd_ospfd;
extern struct cmd_element show_ip_ospf_neighbor_int_detail_cmd_ospfd;
extern struct cmd_element debug_ospf_nsm_cmd_ospfd;
extern struct cmd_element ospf_area_vlink_authtype_cmd_ospfd;
extern struct cmd_element no_ospf_area_filter_list_cmd_ospfd;
extern struct cmd_element show_ip_ospf_neighbor_id_cmd_ospfd;
extern struct cmd_element ospf_passive_interface_cmd_ospfd;
extern struct cmd_element ospf_neighbor_poll_interval_priority_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_external_inter_cmd_ospfd;
extern struct cmd_element no_ospf_area_vlink_authtype_cmd_ospfd;
extern struct cmd_element ospf_area_vlink_authtype_args_md5_cmd_ospfd;
extern struct cmd_element no_ospf_compatible_rfc1583_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_always_metric_type_cmd_ospfd;
extern struct cmd_element no_ospf_area_range_cmd_ospfd;
extern struct cmd_element no_ospf_network_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_intra_cmd_ospfd;
extern struct cmd_element no_ospf_area_stub_cmd_ospfd;
extern struct cmd_element ospf_network_area_cmd_ospfd;
extern struct cmd_element ip_ospf_cost_u32_inet4_cmd_ospfd;
extern struct cmd_element match_ip_address_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_always_metric_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_intra_inter_external_cmd_ospfd;
extern struct cmd_element no_ospf_area_export_list_cmd_ospfd;
extern struct cmd_element no_debug_ospf_lsa_sub_cmd_ospfd;
extern struct cmd_element ip_ospf_message_digest_key_cmd_ospfd;
extern struct cmd_element ospf_area_shortcut_cmd_ospfd;
extern struct cmd_element no_set_metric_val_cmd_ospfd;
extern struct cmd_element ospf_area_import_list_cmd_ospfd;
extern struct cmd_element debug_ospf_lsa_sub_cmd_ospfd;
extern struct cmd_element ospf_area_vlink_authkey_cmd_ospfd;
extern struct cmd_element ospf_compatible_rfc1583_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_inter_intra_external_cmd_ospfd;
extern struct cmd_element ip_ospf_authentication_addr_cmd_ospfd;
extern struct cmd_element no_ospf_max_metric_router_lsa_shutdown_cmd_ospfd;
extern struct cmd_element ospf_distance_source_cmd_ospfd;
extern struct cmd_element no_ospf_authentication_key_cmd_ospfd;
extern struct cmd_element ospf_area_range_not_advertise_cmd_ospfd;
extern struct cmd_element ip_ospf_hello_interval_cmd_ospfd;
extern struct cmd_element ospf_redistribute_source_metric_type_cmd_ospfd;
extern struct cmd_element ip_ospf_authentication_key_addr_cmd_ospfd;
extern struct cmd_element ip_ospf_dead_interval_cmd_ospfd;
extern struct cmd_element ip_ospf_authentication_args_cmd_ospfd;
extern struct cmd_element debug_ospf_ism_cmd_ospfd;
extern struct cmd_element ospf_area_vlink_cmd_ospfd;
extern struct cmd_element no_match_ip_address_cmd_ospfd;
extern struct cmd_element no_ip_ospf_priority_cmd_ospfd;
extern struct cmd_element no_ip_ospf_dead_interval_cmd_ospfd;
extern struct cmd_element ospf_neighbor_priority_poll_interval_cmd_ospfd;
extern struct cmd_element show_ip_ospf_neighbor_all_cmd_ospfd;
extern struct cmd_element no_debug_ospf_nssa_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_always_type_metric_routemap_cmd_ospfd;
extern struct cmd_element no_ospf_distance_ospf_cmd_ospfd;
extern struct cmd_element ospf_abr_type_cmd_ospfd;
extern struct cmd_element no_ip_ospf_network_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_external_intra_cmd_ospfd;
extern struct cmd_element no_ospf_area_vlink_param3_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_always_type_routemap_cmd_ospfd;
extern struct route_map_rule_cmd route_match_ip_address_cmd_ospfd;
extern struct cmd_element no_debug_ospf_lsa_cmd_ospfd;
extern struct cmd_element no_match_ip_nexthop_cmd_ospfd;
extern struct cmd_element no_ospf_area_range_cost_cmd_ospfd;
extern struct cmd_element ospf_redistribute_source_metric_type_routemap_cmd_ospfd;
extern struct cmd_element no_ospf_area_vlink_authkey_cmd_ospfd;
extern struct cmd_element no_ospf_passive_interface_default_cmd_ospfd;
extern struct route_map_rule_cmd route_match_ip_next_hop_prefix_list_cmd_ospfd;
extern struct cmd_element no_debug_ospf_nsm_cmd_ospfd;
extern struct cmd_element ospf_redistribute_source_type_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_external_intra_inter_cmd_ospfd;
extern struct cmd_element no_ip_ospf_dead_interval_addr_cmd_ospfd;
extern struct cmd_element no_ip_ospf_hello_interval_cmd_ospfd;
extern struct cmd_element no_ospf_default_metric_cmd_ospfd;
extern struct cmd_element no_ospf_area_nssa_no_summary_cmd_ospfd;
extern struct cmd_element ospf_neighbor_poll_interval_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_always_cmd_ospfd;
extern struct cmd_element ospf_area_range_cost_cmd_ospfd;
extern struct cmd_element ospf_auto_cost_reference_bandwidth_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_inter_external_cmd_ospfd;
extern struct cmd_element no_debug_ospf_nsm_sub_cmd_ospfd;
extern struct cmd_element no_ospf_priority_cmd_ospfd;
extern struct cmd_element ospf_redistribute_source_cmd_ospfd;
extern struct cmd_element match_ip_next_hop_prefix_list_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_always_type_metric_cmd_ospfd;
extern struct cmd_element ip_ospf_priority_addr_cmd_ospfd;
extern struct cmd_element match_ip_address_prefix_list_cmd_ospfd;
extern struct cmd_element no_ospf_area_vlink_md5_cmd_ospfd;
extern struct cmd_element no_ospf_cost_inet4_cmd_ospfd;
extern struct cmd_element no_ospf_area_range_substitute_cmd_ospfd;
extern struct cmd_element no_ospf_neighbor_cmd_ospfd;
extern struct cmd_element no_debug_ospf_zebra_cmd_ospfd;
extern struct cmd_element ospf_distance_ospf_inter_intra_cmd_ospfd;
extern struct cmd_element no_ospf_area_vlink_param2_cmd_ospfd;
extern struct cmd_element ospf_priority_cmd_ospfd;
extern struct cmd_element ospf_hello_interval_cmd_ospfd;
extern struct cmd_element debug_ospf_zebra_sub_cmd_ospfd;
extern struct cmd_element ospf_timers_spf_cmd_ospfd;
extern struct cmd_element ospf_timers_throttle_spf_cmd_ospfd;
extern struct cmd_element no_ospf_distribute_list_out_cmd_ospfd;
extern struct cmd_element no_ospf_area_range_advertise_cmd_ospfd;
extern struct cmd_element no_ip_ospf_retransmit_interval_cmd_ospfd;
extern struct cmd_element debug_ospf_packet_all_cmd_ospfd;
extern struct cmd_element show_ip_ospf_neighbor_cmd_ospfd;
extern struct cmd_element show_ip_ospf_database_type_id_adv_router_cmd_ospfd;
extern struct cmd_element no_ip_ospf_authentication_key_addr_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_type_metric_routemap_cmd_ospfd;
extern struct cmd_element match_interface_cmd_ospfd;
extern struct cmd_element ospf_area_nssa_translate_cmd_ospfd;
extern struct route_map_rule_cmd route_match_ip_nexthop_cmd_ospfd;
extern struct cmd_element ospf_area_stub_cmd_ospfd;
extern struct cmd_element ospf_dead_interval_cmd_ospfd;
extern struct cmd_element no_ip_ospf_authentication_cmd_ospfd;
extern struct cmd_element ospf_cost_u32_inet4_cmd_ospfd;
extern struct cmd_element ospf_area_range_advertise_cost_cmd_ospfd;
extern struct cmd_element ospf_rfc1583_flag_cmd_ospfd;
extern struct cmd_element no_ip_ospf_authentication_key_cmd_ospfd;
extern struct cmd_element ospf_area_vlink_authtype_authkey_cmd_ospfd;
extern struct cmd_element no_ospf_rfc1583_flag_cmd_ospfd;
extern struct cmd_element ospf_area_vlink_param3_cmd_ospfd;
extern struct cmd_element ip_ospf_transmit_delay_addr_cmd_ospfd;
extern struct cmd_element ospf_area_vlink_param4_cmd_ospfd;
extern struct cmd_element ip_ospf_priority_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_always_type_cmd_ospfd;
extern struct cmd_element no_ospf_retransmit_interval_cmd_ospfd;
extern struct cmd_element debug_ospf_lsa_cmd_ospfd;
extern struct cmd_element no_ospf_passive_interface_addr_cmd_ospfd;
extern struct cmd_element no_ospf_timers_throttle_spf_cmd_ospfd;
extern struct cmd_element no_debug_ospf_packet_send_recv_cmd_ospfd;
extern struct cmd_element no_ospf_refresh_timer_cmd_ospfd;
extern struct cmd_element no_ip_ospf_message_digest_key_addr_cmd_ospfd;
extern struct cmd_element no_ospf_router_id_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_cmd_ospfd;
extern struct cmd_element ospf_distribute_list_out_cmd_ospfd;
extern struct cmd_element show_ip_ospf_cmd_ospfd;
extern struct cmd_element ip_ospf_cost_u32_cmd_ospfd;
extern struct cmd_element no_ospf_distance_source_access_list_cmd_ospfd;
extern struct cmd_element ospf_refresh_timer_cmd_ospfd;
extern struct cmd_element ospf_area_stub_no_summary_cmd_ospfd;
extern struct cmd_element ospf_retransmit_interval_cmd_ospfd;
extern struct cmd_element no_match_ip_next_hop_prefix_list_cmd_ospfd;
extern struct cmd_element ospf_area_vlink_md5_cmd_ospfd;
extern struct cmd_element no_ip_ospf_cost_inet4_cmd_ospfd;
extern struct cmd_element ospf_redistribute_source_routemap_cmd_ospfd;
extern struct cmd_element ospf_area_vlink_authtype_args_cmd_ospfd;
extern struct cmd_element debug_ospf_packet_send_recv_cmd_ospfd;
extern struct cmd_element show_ip_ospf_interface_cmd_ospfd;
extern struct cmd_element no_match_ip_address_prefix_list_cmd_ospfd;
extern struct cmd_element ospf_redistribute_source_type_metric_routemap_cmd_ospfd;
extern struct cmd_element no_debug_ospf_event_cmd_ospfd;
extern struct cmd_element ip_ospf_authentication_args_addr_cmd_ospfd;
extern struct cmd_element show_ip_ospf_database_type_adv_router_cmd_ospfd;
extern struct cmd_element ospf_cost_u32_cmd_ospfd;
extern struct cmd_element no_ospf_default_information_originate_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_metric_cmd_ospfd;
extern struct cmd_element no_ip_ospf_authentication_addr_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_metric_routemap_cmd_ospfd;
extern struct cmd_element show_ip_ospf_border_routers_cmd_ospfd;
extern struct cmd_element ospf_distance_cmd_ospfd;
extern struct cmd_element no_ospf_area_stub_no_summary_cmd_ospfd;
extern struct cmd_element no_ip_ospf_mtu_ignore_cmd_ospfd;
extern struct cmd_element no_ospf_area_shortcut_cmd_ospfd;
extern struct cmd_element no_ospf_area_import_list_cmd_ospfd;
extern struct cmd_element ospf_max_metric_router_lsa_startup_cmd_ospfd;
extern struct cmd_element ospf_default_information_originate_always_metric_routemap_cmd_ospfd;
extern struct cmd_element no_set_metric_type_cmd_ospfd;
extern struct cmd_element ip_ospf_mtu_ignore_addr_cmd_ospfd;
extern struct cmd_element no_ospf_area_vlink_authtype_authkey_cmd_ospfd;
extern struct cmd_element show_ip_ospf_database_type_id_cmd_ospfd;
extern struct cmd_element no_router_ospf_id_cmd_ospfd;
extern struct cmd_element ip_ospf_message_digest_key_addr_cmd_ospfd;
extern struct cmd_element no_ip_ospf_cost_cmd_ospfd;
extern struct cmd_element match_ip_nexthop_cmd_ospfd;
extern struct cmd_element show_ip_ospf_neighbor_detail_all_cmd_ospfd;
extern struct cmd_element debug_ospf_packet_send_recv_detail_cmd_ospfd;
extern struct cmd_element no_ip_ospf_transmit_delay_addr_cmd_ospfd;

void GlobalVars_initializeActiveSet_ospfd()
{
	unsigned long term_debug_ospf_packet__T[5] =  {0, 0, 0, 0, 0};
	struct cmd_node zebra_node__T = 
{
  ZEBRA_NODE,
  "%s(config-router)#",
};
	struct list vertex_list__T =  { .del = ospf_vertex_free };
	struct cmd_node debug_node__T = 
{
  DEBUG_NODE,
  "",
  1 
};
	struct cmd_node interface_node__T = 
{
  INTERFACE_NODE,
  "%s(config-if)# ",
  1
};
	struct cmd_node ospf_node__T = 
{
  OSPF_NODE,
  "%s(config-router)# ",
  1
};
	unsigned long conf_debug_ospf_packet__T[5] =  {0, 0, 0, 0, 0};
	memcpy(&__activeVars->show_ip_ospf_route_cmd__X, &show_ip_ospf_route_cmd_ospfd, sizeof(show_ip_ospf_route_cmd_ospfd));
	__activeVars->pid_file__X =  PATH_OSPFD_PID;
	memcpy(&__activeVars->ospf_area_vlink_param1_cmd__X, &ospf_area_vlink_param1_cmd_ospfd, sizeof(ospf_area_vlink_param1_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_vlink_param1_cmd__X, &no_ospf_area_vlink_param1_cmd_ospfd, sizeof(no_ospf_area_vlink_param1_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_export_list_cmd__X, &ospf_area_export_list_cmd_ospfd, sizeof(ospf_area_export_list_cmd_ospfd));
	memcpy(&__activeVars->ospf_max_metric_router_lsa_shutdown_cmd__X, &ospf_max_metric_router_lsa_shutdown_cmd_ospfd, sizeof(ospf_max_metric_router_lsa_shutdown_cmd_ospfd));
	memcpy(&__activeVars->no_debug_ospf_zebra_sub_cmd__X, &no_debug_ospf_zebra_sub_cmd_ospfd, sizeof(no_debug_ospf_zebra_sub_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_authentication_cmd__X, &ospf_area_authentication_cmd_ospfd, sizeof(ospf_area_authentication_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_dead_interval_minimal_cmd__X, &ip_ospf_dead_interval_minimal_cmd_ospfd, sizeof(ip_ospf_dead_interval_minimal_cmd_ospfd));
	memcpy(&__activeVars->ospf_passive_interface_addr_cmd__X, &ospf_passive_interface_addr_cmd_ospfd, sizeof(ospf_passive_interface_addr_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_retransmit_interval_addr_cmd__X, &no_ip_ospf_retransmit_interval_addr_cmd_ospfd, sizeof(no_ip_ospf_retransmit_interval_addr_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_neighbor_int_cmd__X, &show_ip_ospf_neighbor_int_cmd_ospfd, sizeof(show_ip_ospf_neighbor_int_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_external_inter_intra_cmd__X, &ospf_distance_ospf_external_inter_intra_cmd_ospfd, sizeof(ospf_distance_ospf_external_inter_intra_cmd_ospfd));
	memcpy(&__activeVars->router_ospf_id_cmd__X, &router_ospf_id_cmd_ospfd, sizeof(router_ospf_id_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_hello_interval_addr_cmd__X, &ip_ospf_hello_interval_addr_cmd_ospfd, sizeof(ip_ospf_hello_interval_addr_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_vlink_param4_cmd__X, &no_ospf_area_vlink_param4_cmd_ospfd, sizeof(no_ospf_area_vlink_param4_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_range_advertise_cmd__X, &ospf_area_range_advertise_cmd_ospfd, sizeof(ospf_area_range_advertise_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_metric_type_cmd__X, &ospf_default_information_originate_metric_type_cmd_ospfd, sizeof(ospf_default_information_originate_metric_type_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_mtu_ignore_addr_cmd__X, &no_ip_ospf_mtu_ignore_addr_cmd_ospfd, sizeof(no_ip_ospf_mtu_ignore_addr_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_type_metric_cmd__X, &ospf_default_information_originate_type_metric_cmd_ospfd, sizeof(ospf_default_information_originate_type_metric_cmd_ospfd));
	memcpy(&__activeVars->router_ospf_cmd__X, &router_ospf_cmd_ospfd, sizeof(router_ospf_cmd_ospfd));
	memcpy(&__activeVars->ospf_transmit_delay_cmd__X, &ospf_transmit_delay_cmd_ospfd, sizeof(ospf_transmit_delay_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_default_cost_cmd__X, &no_ospf_area_default_cost_cmd_ospfd, sizeof(no_ospf_area_default_cost_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_range_substitute_cmd__X, &ospf_area_range_substitute_cmd_ospfd, sizeof(ospf_area_range_substitute_cmd_ospfd));
	memcpy(&__activeVars->set_metric_type_cmd__X, &set_metric_type_cmd_ospfd, sizeof(set_metric_type_cmd_ospfd));
	memcpy(&__activeVars->term_debug_ospf_packet__X, &term_debug_ospf_packet__T, sizeof(term_debug_ospf_packet__T));
	memcpy(&__activeVars->no_match_ip_address_prefix_list_val_cmd__X, &no_match_ip_address_prefix_list_val_cmd_ospfd, sizeof(no_match_ip_address_prefix_list_val_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_transmit_delay_cmd__X, &no_ip_ospf_transmit_delay_cmd_ospfd, sizeof(no_ip_ospf_transmit_delay_cmd_ospfd));
	memcpy(&__activeVars->zebra_node__X, &zebra_node__T, sizeof(zebra_node__T));
	memcpy(&__activeVars->ospf_default_information_originate_type_cmd__X, &ospf_default_information_originate_type_cmd_ospfd, sizeof(ospf_default_information_originate_type_cmd_ospfd));
	memcpy(&__activeVars->ospf_authentication_key_cmd__X, &ospf_authentication_key_cmd_ospfd, sizeof(ospf_authentication_key_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_intra_inter_cmd__X, &ospf_distance_ospf_intra_inter_cmd_ospfd, sizeof(ospf_distance_ospf_intra_inter_cmd_ospfd));
	memcpy(&__activeVars->no_debug_ospf_packet_all_cmd__X, &no_debug_ospf_packet_all_cmd_ospfd, sizeof(no_debug_ospf_packet_all_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_intra_external_cmd__X, &ospf_distance_ospf_intra_external_cmd_ospfd, sizeof(ospf_distance_ospf_intra_external_cmd_ospfd));
	memcpy(&__activeVars->ospf_passive_interface_default_cmd__X, &ospf_passive_interface_default_cmd_ospfd, sizeof(ospf_passive_interface_default_cmd_ospfd));
	memcpy(&__activeVars->set_metric_cmd__X, &set_metric_cmd_ospfd, sizeof(set_metric_cmd_ospfd));
	memcpy(&__activeVars->debug_ospf_nsm_sub_cmd__X, &debug_ospf_nsm_sub_cmd_ospfd, sizeof(debug_ospf_nsm_sub_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_dead_interval_addr_cmd__X, &ip_ospf_dead_interval_addr_cmd_ospfd, sizeof(ip_ospf_dead_interval_addr_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_type_routemap_cmd__X, &ospf_default_information_originate_type_routemap_cmd_ospfd, sizeof(ospf_default_information_originate_type_routemap_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_network_cmd__X, &ip_ospf_network_cmd_ospfd, sizeof(ip_ospf_network_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_filter_list_cmd__X, &ospf_area_filter_list_cmd_ospfd, sizeof(ospf_area_filter_list_cmd_ospfd));
	memcpy(&__activeVars->route_set_metric_cmd__X, &route_set_metric_cmd_ospfd, sizeof(route_set_metric_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_vlink_authtype_md5_cmd__X, &ospf_area_vlink_authtype_md5_cmd_ospfd, sizeof(ospf_area_vlink_authtype_md5_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_nssa_translate_no_summary_cmd__X, &ospf_area_nssa_translate_no_summary_cmd_ospfd, sizeof(ospf_area_nssa_translate_no_summary_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_priority_addr_cmd__X, &no_ip_ospf_priority_addr_cmd_ospfd, sizeof(no_ip_ospf_priority_addr_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_log_adjacency_changes_detail_cmd__X, &no_ospf_log_adjacency_changes_detail_cmd_ospfd, sizeof(no_ospf_log_adjacency_changes_detail_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_network_area_cmd__X, &no_ospf_network_area_cmd_ospfd, sizeof(no_ospf_network_area_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_max_metric_router_lsa_admin_cmd__X, &no_ospf_max_metric_router_lsa_admin_cmd_ospfd, sizeof(no_ospf_max_metric_router_lsa_admin_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_metric_cmd__X, &ospf_default_metric_cmd_ospfd, sizeof(ospf_default_metric_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_intra_external_inter_cmd__X, &ospf_distance_ospf_intra_external_inter_cmd_ospfd, sizeof(ospf_distance_ospf_intra_external_inter_cmd_ospfd));
	memcpy(&__activeVars->no_debug_ospf_ism_cmd__X, &no_debug_ospf_ism_cmd_ospfd, sizeof(no_debug_ospf_ism_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_neighbor_poll_interval_cmd__X, &no_ospf_neighbor_poll_interval_cmd_ospfd, sizeof(no_ospf_neighbor_poll_interval_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_vlink_cmd__X, &no_ospf_area_vlink_cmd_ospfd, sizeof(no_ospf_area_vlink_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_mtu_ignore_cmd__X, &ip_ospf_mtu_ignore_cmd_ospfd, sizeof(ip_ospf_mtu_ignore_cmd_ospfd));
	__activeVars->term_debug_ospf_ism__X =  0;
	memcpy(&__activeVars->route_match_interface_cmd__X, &route_match_interface_cmd_ospfd, sizeof(route_match_interface_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_dead_interval_minimal_addr_cmd__X, &ip_ospf_dead_interval_minimal_addr_cmd_ospfd, sizeof(ip_ospf_dead_interval_minimal_addr_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_authentication_cmd__X, &no_ospf_area_authentication_cmd_ospfd, sizeof(no_ospf_area_authentication_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_range_advertise_cost_cmd__X, &no_ospf_area_range_advertise_cost_cmd_ospfd, sizeof(no_ospf_area_range_advertise_cost_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_redistribute_source_cmd__X, &no_ospf_redistribute_source_cmd_ospfd, sizeof(no_ospf_redistribute_source_cmd_ospfd));
	memcpy(&__activeVars->ospf_network_cmd__X, &ospf_network_cmd_ospfd, sizeof(ospf_network_cmd_ospfd));
	__activeVars->conf_debug_ospf_ism__X =  0;
	memcpy(&__activeVars->ospf_redistribute_source_type_routemap_cmd__X, &ospf_redistribute_source_type_routemap_cmd_ospfd, sizeof(ospf_redistribute_source_type_routemap_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_refresh_timer_val_cmd__X, &no_ospf_refresh_timer_val_cmd_ospfd, sizeof(no_ospf_refresh_timer_val_cmd_ospfd));
	memcpy(&__activeVars->no_match_ip_address_val_cmd__X, &no_match_ip_address_val_cmd_ospfd, sizeof(no_match_ip_address_val_cmd_ospfd));
	memcpy(&__activeVars->debug_ospf_zebra_cmd__X, &debug_ospf_zebra_cmd_ospfd, sizeof(debug_ospf_zebra_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_distance_source_cmd__X, &no_ospf_distance_source_cmd_ospfd, sizeof(no_ospf_distance_source_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_passive_interface_cmd__X, &no_ospf_passive_interface_cmd_ospfd, sizeof(no_ospf_passive_interface_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_default_cost_cmd__X, &ospf_area_default_cost_cmd_ospfd, sizeof(ospf_area_default_cost_cmd_ospfd));
	__activeVars->ospf_area_type_msg_max__X =  OSPF_AREA_TYPE_MAX;
	memcpy(&__activeVars->no_ospf_distance_cmd__X, &no_ospf_distance_cmd_ospfd, sizeof(no_ospf_distance_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_retransmit_interval_addr_cmd__X, &ip_ospf_retransmit_interval_addr_cmd_ospfd, sizeof(ip_ospf_retransmit_interval_addr_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_neighbor_detail_cmd__X, &show_ip_ospf_neighbor_detail_cmd_ospfd, sizeof(show_ip_ospf_neighbor_detail_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_message_digest_key_cmd__X, &no_ip_ospf_message_digest_key_cmd_ospfd, sizeof(no_ip_ospf_message_digest_key_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_nssa_cmd__X, &no_ospf_area_nssa_cmd_ospfd, sizeof(no_ospf_area_nssa_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_vlink_authtype_md5_cmd__X, &no_ospf_area_vlink_authtype_md5_cmd_ospfd, sizeof(no_ospf_area_vlink_authtype_md5_cmd_ospfd));
	memcpy(&__activeVars->no_router_ospf_cmd__X, &no_router_ospf_cmd_ospfd, sizeof(no_router_ospf_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_transmit_delay_cmd__X, &ip_ospf_transmit_delay_cmd_ospfd, sizeof(ip_ospf_transmit_delay_cmd_ospfd));
	memcpy(&__activeVars->vertex_list__X, &vertex_list__T, sizeof(vertex_list__T));
	memcpy(&__activeVars->no_ospf_cost_cmd__X, &no_ospf_cost_cmd_ospfd, sizeof(no_ospf_cost_cmd_ospfd));
	memcpy(&__activeVars->debug_ospf_nssa_cmd__X, &debug_ospf_nssa_cmd_ospfd, sizeof(debug_ospf_nssa_cmd_ospfd));
	memcpy(&__activeVars->no_match_interface_val_cmd__X, &no_match_interface_val_cmd_ospfd, sizeof(no_match_interface_val_cmd_ospfd));
	memcpy(&__activeVars->route_match_ip_address_prefix_list_cmd__X, &route_match_ip_address_prefix_list_cmd_ospfd, sizeof(route_match_ip_address_prefix_list_cmd_ospfd));
	memcpy(&__activeVars->debug_ospf_event_cmd__X, &debug_ospf_event_cmd_ospfd, sizeof(debug_ospf_event_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_hello_interval_addr_cmd__X, &no_ip_ospf_hello_interval_addr_cmd_ospfd, sizeof(no_ip_ospf_hello_interval_addr_cmd_ospfd));
	memcpy(&__activeVars->ospf_log_adjacency_changes_detail_cmd__X, &ospf_log_adjacency_changes_detail_cmd_ospfd, sizeof(ospf_log_adjacency_changes_detail_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_metric_type_routemap_cmd__X, &ospf_default_information_originate_metric_type_routemap_cmd_ospfd, sizeof(ospf_default_information_originate_metric_type_routemap_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_source_access_list_cmd__X, &ospf_distance_source_access_list_cmd_ospfd, sizeof(ospf_distance_source_access_list_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_database_cmd__X, &show_ip_ospf_database_cmd_ospfd, sizeof(show_ip_ospf_database_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_hello_interval_cmd__X, &no_ospf_hello_interval_cmd_ospfd, sizeof(no_ospf_hello_interval_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_inter_cmd__X, &ospf_distance_ospf_inter_cmd_ospfd, sizeof(ospf_distance_ospf_inter_cmd_ospfd));
	memcpy(&__activeVars->ospf_redistribute_source_metric_routemap_cmd__X, &ospf_redistribute_source_metric_routemap_cmd_ospfd, sizeof(ospf_redistribute_source_metric_routemap_cmd_ospfd));
	memcpy(&__activeVars->ospf_router_id_cmd__X, &ospf_router_id_cmd_ospfd, sizeof(ospf_router_id_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_authentication_message_digest_cmd__X, &ospf_area_authentication_message_digest_cmd_ospfd, sizeof(ospf_area_authentication_message_digest_cmd_ospfd));
	memcpy(&__activeVars->no_set_metric_cmd__X, &no_set_metric_cmd_ospfd, sizeof(no_set_metric_cmd_ospfd));
	memcpy(&__activeVars->no_match_interface_cmd__X, &no_match_interface_cmd_ospfd, sizeof(no_match_interface_cmd_ospfd));
	memcpy(&__activeVars->no_debug_ospf_packet_send_recv_detail_cmd__X, &no_debug_ospf_packet_send_recv_detail_cmd_ospfd, sizeof(no_debug_ospf_packet_send_recv_detail_cmd_ospfd));
	memcpy(&__activeVars->no_set_metric_type_val_cmd__X, &no_set_metric_type_val_cmd_ospfd, sizeof(no_set_metric_type_val_cmd_ospfd));
	memcpy(&__activeVars->debug_ospf_ism_sub_cmd__X, &debug_ospf_ism_sub_cmd_ospfd, sizeof(debug_ospf_ism_sub_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_inter_external_intra_cmd__X, &ospf_distance_ospf_inter_external_intra_cmd_ospfd, sizeof(ospf_distance_ospf_inter_external_intra_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_range_cmd__X, &ospf_area_range_cmd_ospfd, sizeof(ospf_area_range_cmd_ospfd));
	memcpy(&__activeVars->ospf_max_metric_router_lsa_admin_cmd__X, &ospf_max_metric_router_lsa_admin_cmd_ospfd, sizeof(ospf_max_metric_router_lsa_admin_cmd_ospfd));
	__activeVars->zclient__X =  NULL;
	memcpy(&__activeVars->no_ospf_transmit_delay_cmd__X, &no_ospf_transmit_delay_cmd_ospfd, sizeof(no_ospf_transmit_delay_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_retransmit_interval_cmd__X, &ip_ospf_retransmit_interval_cmd_ospfd, sizeof(ip_ospf_retransmit_interval_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_database_type_id_self_cmd__X, &show_ip_ospf_database_type_id_self_cmd_ospfd, sizeof(show_ip_ospf_database_type_id_self_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_max_metric_router_lsa_startup_cmd__X, &no_ospf_max_metric_router_lsa_startup_cmd_ospfd, sizeof(no_ospf_max_metric_router_lsa_startup_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_auto_cost_reference_bandwidth_cmd__X, &no_ospf_auto_cost_reference_bandwidth_cmd_ospfd, sizeof(no_ospf_auto_cost_reference_bandwidth_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_nssa_no_summary_cmd__X, &ospf_area_nssa_no_summary_cmd_ospfd, sizeof(ospf_area_nssa_no_summary_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_routemap_cmd__X, &ospf_default_information_originate_routemap_cmd_ospfd, sizeof(ospf_default_information_originate_routemap_cmd_ospfd));
	memcpy(&__activeVars->ospf_redistribute_source_type_metric_cmd__X, &ospf_redistribute_source_type_metric_cmd_ospfd, sizeof(ospf_redistribute_source_type_metric_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_external_cmd__X, &ospf_distance_ospf_external_cmd_ospfd, sizeof(ospf_distance_ospf_external_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_message_digest_key_cmd__X, &no_ospf_message_digest_key_cmd_ospfd, sizeof(no_ospf_message_digest_key_cmd_ospfd));
	memcpy(&__activeVars->ospf_log_adjacency_changes_cmd__X, &ospf_log_adjacency_changes_cmd_ospfd, sizeof(ospf_log_adjacency_changes_cmd_ospfd));
	memcpy(&__activeVars->ospf_message_digest_key_cmd__X, &ospf_message_digest_key_cmd_ospfd, sizeof(ospf_message_digest_key_cmd_ospfd));
	memcpy(&__activeVars->debug_node__X, &debug_node__T, sizeof(debug_node__T));
	memcpy(&__activeVars->ospf_redistribute_source_metric_cmd__X, &ospf_redistribute_source_metric_cmd_ospfd, sizeof(ospf_redistribute_source_metric_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_authentication_key_cmd__X, &ip_ospf_authentication_key_cmd_ospfd, sizeof(ip_ospf_authentication_key_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_neighbor_priority_pollinterval_cmd__X, &no_ospf_neighbor_priority_pollinterval_cmd_ospfd, sizeof(no_ospf_neighbor_priority_pollinterval_cmd_ospfd));
	memcpy(&__activeVars->route_set_metric_type_cmd__X, &route_set_metric_type_cmd_ospfd, sizeof(route_set_metric_type_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_dead_interval_cmd__X, &no_ospf_dead_interval_cmd_ospfd, sizeof(no_ospf_dead_interval_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_log_adjacency_changes_cmd__X, &no_ospf_log_adjacency_changes_cmd_ospfd, sizeof(no_ospf_log_adjacency_changes_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_authentication_cmd__X, &ip_ospf_authentication_cmd_ospfd, sizeof(ip_ospf_authentication_cmd_ospfd));
	memcpy(&__activeVars->ospf_neighbor_priority_cmd__X, &ospf_neighbor_priority_cmd_ospfd, sizeof(ospf_neighbor_priority_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_abr_type_cmd__X, &no_ospf_abr_type_cmd_ospfd, sizeof(no_ospf_abr_type_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_database_type_self_cmd__X, &show_ip_ospf_database_type_self_cmd_ospfd, sizeof(show_ip_ospf_database_type_self_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_database_type_cmd__X, &show_ip_ospf_database_type_cmd_ospfd, sizeof(show_ip_ospf_database_type_cmd_ospfd));
	__activeVars->vlink_count__X =  0;
	memcpy(&__activeVars->no_match_ip_next_hop_prefix_list_val_cmd__X, &no_match_ip_next_hop_prefix_list_val_cmd_ospfd, sizeof(no_match_ip_next_hop_prefix_list_val_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_vlink_authtype_args_authkey_cmd__X, &ospf_area_vlink_authtype_args_authkey_cmd_ospfd, sizeof(ospf_area_vlink_authtype_args_authkey_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_default_metric_val_cmd__X, &no_ospf_default_metric_val_cmd_ospfd, sizeof(no_ospf_default_metric_val_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_always_metric_type_routemap_cmd__X, &ospf_default_information_originate_always_metric_type_routemap_cmd_ospfd, sizeof(ospf_default_information_originate_always_metric_type_routemap_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_always_routemap_cmd__X, &ospf_default_information_originate_always_routemap_cmd_ospfd, sizeof(ospf_default_information_originate_always_routemap_cmd_ospfd));
	__activeVars->conf_debug_ospf_nsm__X =  0;
	memcpy(&__activeVars->ospf_area_vlink_param2_cmd__X, &ospf_area_vlink_param2_cmd_ospfd, sizeof(ospf_area_vlink_param2_cmd_ospfd));
	memcpy(&__activeVars->interface_node__X, &interface_node__T, sizeof(interface_node__T));
	memcpy(&__activeVars->no_ospf_neighbor_priority_cmd__X, &no_ospf_neighbor_priority_cmd_ospfd, sizeof(no_ospf_neighbor_priority_cmd_ospfd));
	memcpy(&__activeVars->no_match_ip_nexthop_val_cmd__X, &no_match_ip_nexthop_val_cmd_ospfd, sizeof(no_match_ip_nexthop_val_cmd_ospfd));
	memcpy(&__activeVars->show_debugging_ospf_cmd__X, &show_debugging_ospf_cmd_ospfd, sizeof(show_debugging_ospf_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_nssa_cmd__X, &ospf_area_nssa_cmd_ospfd, sizeof(ospf_area_nssa_cmd_ospfd));
	memcpy(&__activeVars->no_debug_ospf_ism_sub_cmd__X, &no_debug_ospf_ism_sub_cmd_ospfd, sizeof(no_debug_ospf_ism_sub_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_neighbor_int_detail_cmd__X, &show_ip_ospf_neighbor_int_detail_cmd_ospfd, sizeof(show_ip_ospf_neighbor_int_detail_cmd_ospfd));
	memcpy(&__activeVars->debug_ospf_nsm_cmd__X, &debug_ospf_nsm_cmd_ospfd, sizeof(debug_ospf_nsm_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_vlink_authtype_cmd__X, &ospf_area_vlink_authtype_cmd_ospfd, sizeof(ospf_area_vlink_authtype_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_filter_list_cmd__X, &no_ospf_area_filter_list_cmd_ospfd, sizeof(no_ospf_area_filter_list_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_neighbor_id_cmd__X, &show_ip_ospf_neighbor_id_cmd_ospfd, sizeof(show_ip_ospf_neighbor_id_cmd_ospfd));
	memcpy(&__activeVars->ospf_node__X, &ospf_node__T, sizeof(ospf_node__T));
	memcpy(&__activeVars->ospf_passive_interface_cmd__X, &ospf_passive_interface_cmd_ospfd, sizeof(ospf_passive_interface_cmd_ospfd));
	memcpy(&__activeVars->ospf_neighbor_poll_interval_priority_cmd__X, &ospf_neighbor_poll_interval_priority_cmd_ospfd, sizeof(ospf_neighbor_poll_interval_priority_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_external_inter_cmd__X, &ospf_distance_ospf_external_inter_cmd_ospfd, sizeof(ospf_distance_ospf_external_inter_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_vlink_authtype_cmd__X, &no_ospf_area_vlink_authtype_cmd_ospfd, sizeof(no_ospf_area_vlink_authtype_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_vlink_authtype_args_md5_cmd__X, &ospf_area_vlink_authtype_args_md5_cmd_ospfd, sizeof(ospf_area_vlink_authtype_args_md5_cmd_ospfd));
	__activeVars->conf_debug_ospf_lsa__X =  0;
	memcpy(&__activeVars->no_ospf_compatible_rfc1583_cmd__X, &no_ospf_compatible_rfc1583_cmd_ospfd, sizeof(no_ospf_compatible_rfc1583_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_always_metric_type_cmd__X, &ospf_default_information_originate_always_metric_type_cmd_ospfd, sizeof(ospf_default_information_originate_always_metric_type_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_range_cmd__X, &no_ospf_area_range_cmd_ospfd, sizeof(no_ospf_area_range_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_network_cmd__X, &no_ospf_network_cmd_ospfd, sizeof(no_ospf_network_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_intra_cmd__X, &ospf_distance_ospf_intra_cmd_ospfd, sizeof(ospf_distance_ospf_intra_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_stub_cmd__X, &no_ospf_area_stub_cmd_ospfd, sizeof(no_ospf_area_stub_cmd_ospfd));
	memcpy(&__activeVars->ospf_network_area_cmd__X, &ospf_network_area_cmd_ospfd, sizeof(ospf_network_area_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_cost_u32_inet4_cmd__X, &ip_ospf_cost_u32_inet4_cmd_ospfd, sizeof(ip_ospf_cost_u32_inet4_cmd_ospfd));
	memcpy(&__activeVars->match_ip_address_cmd__X, &match_ip_address_cmd_ospfd, sizeof(match_ip_address_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_always_metric_cmd__X, &ospf_default_information_originate_always_metric_cmd_ospfd, sizeof(ospf_default_information_originate_always_metric_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_intra_inter_external_cmd__X, &ospf_distance_ospf_intra_inter_external_cmd_ospfd, sizeof(ospf_distance_ospf_intra_inter_external_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_export_list_cmd__X, &no_ospf_area_export_list_cmd_ospfd, sizeof(no_ospf_area_export_list_cmd_ospfd));
	memcpy(&__activeVars->no_debug_ospf_lsa_sub_cmd__X, &no_debug_ospf_lsa_sub_cmd_ospfd, sizeof(no_debug_ospf_lsa_sub_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_message_digest_key_cmd__X, &ip_ospf_message_digest_key_cmd_ospfd, sizeof(ip_ospf_message_digest_key_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_shortcut_cmd__X, &ospf_area_shortcut_cmd_ospfd, sizeof(ospf_area_shortcut_cmd_ospfd));
	memcpy(&__activeVars->no_set_metric_val_cmd__X, &no_set_metric_val_cmd_ospfd, sizeof(no_set_metric_val_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_import_list_cmd__X, &ospf_area_import_list_cmd_ospfd, sizeof(ospf_area_import_list_cmd_ospfd));
	memcpy(&__activeVars->debug_ospf_lsa_sub_cmd__X, &debug_ospf_lsa_sub_cmd_ospfd, sizeof(debug_ospf_lsa_sub_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_vlink_authkey_cmd__X, &ospf_area_vlink_authkey_cmd_ospfd, sizeof(ospf_area_vlink_authkey_cmd_ospfd));
	memcpy(&__activeVars->ospf_compatible_rfc1583_cmd__X, &ospf_compatible_rfc1583_cmd_ospfd, sizeof(ospf_compatible_rfc1583_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_inter_intra_external_cmd__X, &ospf_distance_ospf_inter_intra_external_cmd_ospfd, sizeof(ospf_distance_ospf_inter_intra_external_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_authentication_addr_cmd__X, &ip_ospf_authentication_addr_cmd_ospfd, sizeof(ip_ospf_authentication_addr_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_max_metric_router_lsa_shutdown_cmd__X, &no_ospf_max_metric_router_lsa_shutdown_cmd_ospfd, sizeof(no_ospf_max_metric_router_lsa_shutdown_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_source_cmd__X, &ospf_distance_source_cmd_ospfd, sizeof(ospf_distance_source_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_authentication_key_cmd__X, &no_ospf_authentication_key_cmd_ospfd, sizeof(no_ospf_authentication_key_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_range_not_advertise_cmd__X, &ospf_area_range_not_advertise_cmd_ospfd, sizeof(ospf_area_range_not_advertise_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_hello_interval_cmd__X, &ip_ospf_hello_interval_cmd_ospfd, sizeof(ip_ospf_hello_interval_cmd_ospfd));
	memcpy(&__activeVars->ospf_redistribute_source_metric_type_cmd__X, &ospf_redistribute_source_metric_type_cmd_ospfd, sizeof(ospf_redistribute_source_metric_type_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_authentication_key_addr_cmd__X, &ip_ospf_authentication_key_addr_cmd_ospfd, sizeof(ip_ospf_authentication_key_addr_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_dead_interval_cmd__X, &ip_ospf_dead_interval_cmd_ospfd, sizeof(ip_ospf_dead_interval_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_authentication_args_cmd__X, &ip_ospf_authentication_args_cmd_ospfd, sizeof(ip_ospf_authentication_args_cmd_ospfd));
	memcpy(&__activeVars->debug_ospf_ism_cmd__X, &debug_ospf_ism_cmd_ospfd, sizeof(debug_ospf_ism_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_vlink_cmd__X, &ospf_area_vlink_cmd_ospfd, sizeof(ospf_area_vlink_cmd_ospfd));
	memcpy(&__activeVars->no_match_ip_address_cmd__X, &no_match_ip_address_cmd_ospfd, sizeof(no_match_ip_address_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_priority_cmd__X, &no_ip_ospf_priority_cmd_ospfd, sizeof(no_ip_ospf_priority_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_dead_interval_cmd__X, &no_ip_ospf_dead_interval_cmd_ospfd, sizeof(no_ip_ospf_dead_interval_cmd_ospfd));
	memcpy(&__activeVars->ospf_neighbor_priority_poll_interval_cmd__X, &ospf_neighbor_priority_poll_interval_cmd_ospfd, sizeof(ospf_neighbor_priority_poll_interval_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_neighbor_all_cmd__X, &show_ip_ospf_neighbor_all_cmd_ospfd, sizeof(show_ip_ospf_neighbor_all_cmd_ospfd));
	memcpy(&__activeVars->no_debug_ospf_nssa_cmd__X, &no_debug_ospf_nssa_cmd_ospfd, sizeof(no_debug_ospf_nssa_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_always_type_metric_routemap_cmd__X, &ospf_default_information_originate_always_type_metric_routemap_cmd_ospfd, sizeof(ospf_default_information_originate_always_type_metric_routemap_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_distance_ospf_cmd__X, &no_ospf_distance_ospf_cmd_ospfd, sizeof(no_ospf_distance_ospf_cmd_ospfd));
	memcpy(&__activeVars->ospf_abr_type_cmd__X, &ospf_abr_type_cmd_ospfd, sizeof(ospf_abr_type_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_network_cmd__X, &no_ip_ospf_network_cmd_ospfd, sizeof(no_ip_ospf_network_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_external_intra_cmd__X, &ospf_distance_ospf_external_intra_cmd_ospfd, sizeof(ospf_distance_ospf_external_intra_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_vlink_param3_cmd__X, &no_ospf_area_vlink_param3_cmd_ospfd, sizeof(no_ospf_area_vlink_param3_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_always_type_routemap_cmd__X, &ospf_default_information_originate_always_type_routemap_cmd_ospfd, sizeof(ospf_default_information_originate_always_type_routemap_cmd_ospfd));
	memcpy(&__activeVars->route_match_ip_address_cmd__X, &route_match_ip_address_cmd_ospfd, sizeof(route_match_ip_address_cmd_ospfd));
	memcpy(&__activeVars->no_debug_ospf_lsa_cmd__X, &no_debug_ospf_lsa_cmd_ospfd, sizeof(no_debug_ospf_lsa_cmd_ospfd));
	memcpy(&__activeVars->no_match_ip_nexthop_cmd__X, &no_match_ip_nexthop_cmd_ospfd, sizeof(no_match_ip_nexthop_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_range_cost_cmd__X, &no_ospf_area_range_cost_cmd_ospfd, sizeof(no_ospf_area_range_cost_cmd_ospfd));
	memcpy(&__activeVars->ospf_redistribute_source_metric_type_routemap_cmd__X, &ospf_redistribute_source_metric_type_routemap_cmd_ospfd, sizeof(ospf_redistribute_source_metric_type_routemap_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_vlink_authkey_cmd__X, &no_ospf_area_vlink_authkey_cmd_ospfd, sizeof(no_ospf_area_vlink_authkey_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_passive_interface_default_cmd__X, &no_ospf_passive_interface_default_cmd_ospfd, sizeof(no_ospf_passive_interface_default_cmd_ospfd));
	__activeVars->term_debug_ospf_event__X =  0;
	memcpy(&__activeVars->route_match_ip_next_hop_prefix_list_cmd__X, &route_match_ip_next_hop_prefix_list_cmd_ospfd, sizeof(route_match_ip_next_hop_prefix_list_cmd_ospfd));
	memcpy(&__activeVars->no_debug_ospf_nsm_cmd__X, &no_debug_ospf_nsm_cmd_ospfd, sizeof(no_debug_ospf_nsm_cmd_ospfd));
	memcpy(&__activeVars->ospf_redistribute_source_type_cmd__X, &ospf_redistribute_source_type_cmd_ospfd, sizeof(ospf_redistribute_source_type_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_external_intra_inter_cmd__X, &ospf_distance_ospf_external_intra_inter_cmd_ospfd, sizeof(ospf_distance_ospf_external_intra_inter_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_dead_interval_addr_cmd__X, &no_ip_ospf_dead_interval_addr_cmd_ospfd, sizeof(no_ip_ospf_dead_interval_addr_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_hello_interval_cmd__X, &no_ip_ospf_hello_interval_cmd_ospfd, sizeof(no_ip_ospf_hello_interval_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_default_metric_cmd__X, &no_ospf_default_metric_cmd_ospfd, sizeof(no_ospf_default_metric_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_nssa_no_summary_cmd__X, &no_ospf_area_nssa_no_summary_cmd_ospfd, sizeof(no_ospf_area_nssa_no_summary_cmd_ospfd));
	memcpy(&__activeVars->ospf_neighbor_poll_interval_cmd__X, &ospf_neighbor_poll_interval_cmd_ospfd, sizeof(ospf_neighbor_poll_interval_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_always_cmd__X, &ospf_default_information_originate_always_cmd_ospfd, sizeof(ospf_default_information_originate_always_cmd_ospfd));
	__activeVars->conf_debug_ospf_zebra__X =  0;
	memcpy(&__activeVars->ospf_area_range_cost_cmd__X, &ospf_area_range_cost_cmd_ospfd, sizeof(ospf_area_range_cost_cmd_ospfd));
	memcpy(&__activeVars->ospf_auto_cost_reference_bandwidth_cmd__X, &ospf_auto_cost_reference_bandwidth_cmd_ospfd, sizeof(ospf_auto_cost_reference_bandwidth_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_inter_external_cmd__X, &ospf_distance_ospf_inter_external_cmd_ospfd, sizeof(ospf_distance_ospf_inter_external_cmd_ospfd));
	memcpy(&__activeVars->no_debug_ospf_nsm_sub_cmd__X, &no_debug_ospf_nsm_sub_cmd_ospfd, sizeof(no_debug_ospf_nsm_sub_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_priority_cmd__X, &no_ospf_priority_cmd_ospfd, sizeof(no_ospf_priority_cmd_ospfd));
	memcpy(&__activeVars->ospf_redistribute_source_cmd__X, &ospf_redistribute_source_cmd_ospfd, sizeof(ospf_redistribute_source_cmd_ospfd));
	memcpy(&__activeVars->match_ip_next_hop_prefix_list_cmd__X, &match_ip_next_hop_prefix_list_cmd_ospfd, sizeof(match_ip_next_hop_prefix_list_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_always_type_metric_cmd__X, &ospf_default_information_originate_always_type_metric_cmd_ospfd, sizeof(ospf_default_information_originate_always_type_metric_cmd_ospfd));
	__activeVars->term_debug_ospf_nssa__X =  0;
	memcpy(&__activeVars->ip_ospf_priority_addr_cmd__X, &ip_ospf_priority_addr_cmd_ospfd, sizeof(ip_ospf_priority_addr_cmd_ospfd));
	memcpy(&__activeVars->match_ip_address_prefix_list_cmd__X, &match_ip_address_prefix_list_cmd_ospfd, sizeof(match_ip_address_prefix_list_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_vlink_md5_cmd__X, &no_ospf_area_vlink_md5_cmd_ospfd, sizeof(no_ospf_area_vlink_md5_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_cost_inet4_cmd__X, &no_ospf_cost_inet4_cmd_ospfd, sizeof(no_ospf_cost_inet4_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_range_substitute_cmd__X, &no_ospf_area_range_substitute_cmd_ospfd, sizeof(no_ospf_area_range_substitute_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_neighbor_cmd__X, &no_ospf_neighbor_cmd_ospfd, sizeof(no_ospf_neighbor_cmd_ospfd));
	memcpy(&__activeVars->no_debug_ospf_zebra_cmd__X, &no_debug_ospf_zebra_cmd_ospfd, sizeof(no_debug_ospf_zebra_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_ospf_inter_intra_cmd__X, &ospf_distance_ospf_inter_intra_cmd_ospfd, sizeof(ospf_distance_ospf_inter_intra_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_vlink_param2_cmd__X, &no_ospf_area_vlink_param2_cmd_ospfd, sizeof(no_ospf_area_vlink_param2_cmd_ospfd));
	memcpy(&__activeVars->ospf_priority_cmd__X, &ospf_priority_cmd_ospfd, sizeof(ospf_priority_cmd_ospfd));
	memcpy(&__activeVars->ospf_hello_interval_cmd__X, &ospf_hello_interval_cmd_ospfd, sizeof(ospf_hello_interval_cmd_ospfd));
	memcpy(&__activeVars->debug_ospf_zebra_sub_cmd__X, &debug_ospf_zebra_sub_cmd_ospfd, sizeof(debug_ospf_zebra_sub_cmd_ospfd));
	memcpy(&__activeVars->ospf_timers_spf_cmd__X, &ospf_timers_spf_cmd_ospfd, sizeof(ospf_timers_spf_cmd_ospfd));
	memcpy(&__activeVars->ospf_timers_throttle_spf_cmd__X, &ospf_timers_throttle_spf_cmd_ospfd, sizeof(ospf_timers_throttle_spf_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_distribute_list_out_cmd__X, &no_ospf_distribute_list_out_cmd_ospfd, sizeof(no_ospf_distribute_list_out_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_range_advertise_cmd__X, &no_ospf_area_range_advertise_cmd_ospfd, sizeof(no_ospf_area_range_advertise_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_retransmit_interval_cmd__X, &no_ip_ospf_retransmit_interval_cmd_ospfd, sizeof(no_ip_ospf_retransmit_interval_cmd_ospfd));
	memcpy(&__activeVars->debug_ospf_packet_all_cmd__X, &debug_ospf_packet_all_cmd_ospfd, sizeof(debug_ospf_packet_all_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_neighbor_cmd__X, &show_ip_ospf_neighbor_cmd_ospfd, sizeof(show_ip_ospf_neighbor_cmd_ospfd));
	__activeVars->term_debug_ospf_zebra__X =  0;
	memcpy(&__activeVars->show_ip_ospf_database_type_id_adv_router_cmd__X, &show_ip_ospf_database_type_id_adv_router_cmd_ospfd, sizeof(show_ip_ospf_database_type_id_adv_router_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_authentication_key_addr_cmd__X, &no_ip_ospf_authentication_key_addr_cmd_ospfd, sizeof(no_ip_ospf_authentication_key_addr_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_type_metric_routemap_cmd__X, &ospf_default_information_originate_type_metric_routemap_cmd_ospfd, sizeof(ospf_default_information_originate_type_metric_routemap_cmd_ospfd));
	memcpy(&__activeVars->match_interface_cmd__X, &match_interface_cmd_ospfd, sizeof(match_interface_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_nssa_translate_cmd__X, &ospf_area_nssa_translate_cmd_ospfd, sizeof(ospf_area_nssa_translate_cmd_ospfd));
	memcpy(&__activeVars->route_match_ip_nexthop_cmd__X, &route_match_ip_nexthop_cmd_ospfd, sizeof(route_match_ip_nexthop_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_stub_cmd__X, &ospf_area_stub_cmd_ospfd, sizeof(ospf_area_stub_cmd_ospfd));
	memcpy(&__activeVars->ospf_dead_interval_cmd__X, &ospf_dead_interval_cmd_ospfd, sizeof(ospf_dead_interval_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_authentication_cmd__X, &no_ip_ospf_authentication_cmd_ospfd, sizeof(no_ip_ospf_authentication_cmd_ospfd));
	memcpy(&__activeVars->ospf_cost_u32_inet4_cmd__X, &ospf_cost_u32_inet4_cmd_ospfd, sizeof(ospf_cost_u32_inet4_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_range_advertise_cost_cmd__X, &ospf_area_range_advertise_cost_cmd_ospfd, sizeof(ospf_area_range_advertise_cost_cmd_ospfd));
	memcpy(&__activeVars->ospf_rfc1583_flag_cmd__X, &ospf_rfc1583_flag_cmd_ospfd, sizeof(ospf_rfc1583_flag_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_authentication_key_cmd__X, &no_ip_ospf_authentication_key_cmd_ospfd, sizeof(no_ip_ospf_authentication_key_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_vlink_authtype_authkey_cmd__X, &ospf_area_vlink_authtype_authkey_cmd_ospfd, sizeof(ospf_area_vlink_authtype_authkey_cmd_ospfd));
	__activeVars->conf_debug_ospf_event__X =  0;
	memcpy(&__activeVars->no_ospf_rfc1583_flag_cmd__X, &no_ospf_rfc1583_flag_cmd_ospfd, sizeof(no_ospf_rfc1583_flag_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_vlink_param3_cmd__X, &ospf_area_vlink_param3_cmd_ospfd, sizeof(ospf_area_vlink_param3_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_transmit_delay_addr_cmd__X, &ip_ospf_transmit_delay_addr_cmd_ospfd, sizeof(ip_ospf_transmit_delay_addr_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_vlink_param4_cmd__X, &ospf_area_vlink_param4_cmd_ospfd, sizeof(ospf_area_vlink_param4_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_priority_cmd__X, &ip_ospf_priority_cmd_ospfd, sizeof(ip_ospf_priority_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_always_type_cmd__X, &ospf_default_information_originate_always_type_cmd_ospfd, sizeof(ospf_default_information_originate_always_type_cmd_ospfd));
	memcpy(&__activeVars->conf_debug_ospf_packet__X, &conf_debug_ospf_packet__T, sizeof(conf_debug_ospf_packet__T));
	memcpy(&__activeVars->no_ospf_retransmit_interval_cmd__X, &no_ospf_retransmit_interval_cmd_ospfd, sizeof(no_ospf_retransmit_interval_cmd_ospfd));
	memcpy(&__activeVars->debug_ospf_lsa_cmd__X, &debug_ospf_lsa_cmd_ospfd, sizeof(debug_ospf_lsa_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_passive_interface_addr_cmd__X, &no_ospf_passive_interface_addr_cmd_ospfd, sizeof(no_ospf_passive_interface_addr_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_timers_throttle_spf_cmd__X, &no_ospf_timers_throttle_spf_cmd_ospfd, sizeof(no_ospf_timers_throttle_spf_cmd_ospfd));
	memcpy(&__activeVars->no_debug_ospf_packet_send_recv_cmd__X, &no_debug_ospf_packet_send_recv_cmd_ospfd, sizeof(no_debug_ospf_packet_send_recv_cmd_ospfd));
	__activeVars->conf_debug_ospf_nssa__X =  0;
	memcpy(&__activeVars->no_ospf_refresh_timer_cmd__X, &no_ospf_refresh_timer_cmd_ospfd, sizeof(no_ospf_refresh_timer_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_message_digest_key_addr_cmd__X, &no_ip_ospf_message_digest_key_addr_cmd_ospfd, sizeof(no_ip_ospf_message_digest_key_addr_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_router_id_cmd__X, &no_ospf_router_id_cmd_ospfd, sizeof(no_ospf_router_id_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_cmd__X, &ospf_default_information_originate_cmd_ospfd, sizeof(ospf_default_information_originate_cmd_ospfd));
	memcpy(&__activeVars->ospf_distribute_list_out_cmd__X, &ospf_distribute_list_out_cmd_ospfd, sizeof(ospf_distribute_list_out_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_cmd__X, &show_ip_ospf_cmd_ospfd, sizeof(show_ip_ospf_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_cost_u32_cmd__X, &ip_ospf_cost_u32_cmd_ospfd, sizeof(ip_ospf_cost_u32_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_distance_source_access_list_cmd__X, &no_ospf_distance_source_access_list_cmd_ospfd, sizeof(no_ospf_distance_source_access_list_cmd_ospfd));
	memcpy(&__activeVars->ospf_refresh_timer_cmd__X, &ospf_refresh_timer_cmd_ospfd, sizeof(ospf_refresh_timer_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_stub_no_summary_cmd__X, &ospf_area_stub_no_summary_cmd_ospfd, sizeof(ospf_area_stub_no_summary_cmd_ospfd));
	memcpy(&__activeVars->ospf_retransmit_interval_cmd__X, &ospf_retransmit_interval_cmd_ospfd, sizeof(ospf_retransmit_interval_cmd_ospfd));
	memcpy(&__activeVars->no_match_ip_next_hop_prefix_list_cmd__X, &no_match_ip_next_hop_prefix_list_cmd_ospfd, sizeof(no_match_ip_next_hop_prefix_list_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_vlink_md5_cmd__X, &ospf_area_vlink_md5_cmd_ospfd, sizeof(ospf_area_vlink_md5_cmd_ospfd));
	__activeVars->term_debug_ospf_nsm__X =  0;
	memcpy(&__activeVars->no_ip_ospf_cost_inet4_cmd__X, &no_ip_ospf_cost_inet4_cmd_ospfd, sizeof(no_ip_ospf_cost_inet4_cmd_ospfd));
	memcpy(&__activeVars->ospf_redistribute_source_routemap_cmd__X, &ospf_redistribute_source_routemap_cmd_ospfd, sizeof(ospf_redistribute_source_routemap_cmd_ospfd));
	memcpy(&__activeVars->ospf_area_vlink_authtype_args_cmd__X, &ospf_area_vlink_authtype_args_cmd_ospfd, sizeof(ospf_area_vlink_authtype_args_cmd_ospfd));
	memcpy(&__activeVars->debug_ospf_packet_send_recv_cmd__X, &debug_ospf_packet_send_recv_cmd_ospfd, sizeof(debug_ospf_packet_send_recv_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_interface_cmd__X, &show_ip_ospf_interface_cmd_ospfd, sizeof(show_ip_ospf_interface_cmd_ospfd));
	memcpy(&__activeVars->no_match_ip_address_prefix_list_cmd__X, &no_match_ip_address_prefix_list_cmd_ospfd, sizeof(no_match_ip_address_prefix_list_cmd_ospfd));
	memcpy(&__activeVars->ospf_redistribute_source_type_metric_routemap_cmd__X, &ospf_redistribute_source_type_metric_routemap_cmd_ospfd, sizeof(ospf_redistribute_source_type_metric_routemap_cmd_ospfd));
	memcpy(&__activeVars->no_debug_ospf_event_cmd__X, &no_debug_ospf_event_cmd_ospfd, sizeof(no_debug_ospf_event_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_authentication_args_addr_cmd__X, &ip_ospf_authentication_args_addr_cmd_ospfd, sizeof(ip_ospf_authentication_args_addr_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_database_type_adv_router_cmd__X, &show_ip_ospf_database_type_adv_router_cmd_ospfd, sizeof(show_ip_ospf_database_type_adv_router_cmd_ospfd));
	memcpy(&__activeVars->ospf_cost_u32_cmd__X, &ospf_cost_u32_cmd_ospfd, sizeof(ospf_cost_u32_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_default_information_originate_cmd__X, &no_ospf_default_information_originate_cmd_ospfd, sizeof(no_ospf_default_information_originate_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_metric_cmd__X, &ospf_default_information_originate_metric_cmd_ospfd, sizeof(ospf_default_information_originate_metric_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_authentication_addr_cmd__X, &no_ip_ospf_authentication_addr_cmd_ospfd, sizeof(no_ip_ospf_authentication_addr_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_metric_routemap_cmd__X, &ospf_default_information_originate_metric_routemap_cmd_ospfd, sizeof(ospf_default_information_originate_metric_routemap_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_border_routers_cmd__X, &show_ip_ospf_border_routers_cmd_ospfd, sizeof(show_ip_ospf_border_routers_cmd_ospfd));
	memcpy(&__activeVars->ospf_distance_cmd__X, &ospf_distance_cmd_ospfd, sizeof(ospf_distance_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_stub_no_summary_cmd__X, &no_ospf_area_stub_no_summary_cmd_ospfd, sizeof(no_ospf_area_stub_no_summary_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_mtu_ignore_cmd__X, &no_ip_ospf_mtu_ignore_cmd_ospfd, sizeof(no_ip_ospf_mtu_ignore_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_shortcut_cmd__X, &no_ospf_area_shortcut_cmd_ospfd, sizeof(no_ospf_area_shortcut_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_import_list_cmd__X, &no_ospf_area_import_list_cmd_ospfd, sizeof(no_ospf_area_import_list_cmd_ospfd));
	memcpy(&__activeVars->ospf_max_metric_router_lsa_startup_cmd__X, &ospf_max_metric_router_lsa_startup_cmd_ospfd, sizeof(ospf_max_metric_router_lsa_startup_cmd_ospfd));
	memcpy(&__activeVars->ospf_default_information_originate_always_metric_routemap_cmd__X, &ospf_default_information_originate_always_metric_routemap_cmd_ospfd, sizeof(ospf_default_information_originate_always_metric_routemap_cmd_ospfd));
	memcpy(&__activeVars->no_set_metric_type_cmd__X, &no_set_metric_type_cmd_ospfd, sizeof(no_set_metric_type_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_mtu_ignore_addr_cmd__X, &ip_ospf_mtu_ignore_addr_cmd_ospfd, sizeof(ip_ospf_mtu_ignore_addr_cmd_ospfd));
	memcpy(&__activeVars->no_ospf_area_vlink_authtype_authkey_cmd__X, &no_ospf_area_vlink_authtype_authkey_cmd_ospfd, sizeof(no_ospf_area_vlink_authtype_authkey_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_database_type_id_cmd__X, &show_ip_ospf_database_type_id_cmd_ospfd, sizeof(show_ip_ospf_database_type_id_cmd_ospfd));
	memcpy(&__activeVars->no_router_ospf_id_cmd__X, &no_router_ospf_id_cmd_ospfd, sizeof(no_router_ospf_id_cmd_ospfd));
	memcpy(&__activeVars->ip_ospf_message_digest_key_addr_cmd__X, &ip_ospf_message_digest_key_addr_cmd_ospfd, sizeof(ip_ospf_message_digest_key_addr_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_cost_cmd__X, &no_ip_ospf_cost_cmd_ospfd, sizeof(no_ip_ospf_cost_cmd_ospfd));
	__activeVars->term_debug_ospf_lsa__X =  0;
	memcpy(&__activeVars->match_ip_nexthop_cmd__X, &match_ip_nexthop_cmd_ospfd, sizeof(match_ip_nexthop_cmd_ospfd));
	memcpy(&__activeVars->show_ip_ospf_neighbor_detail_all_cmd__X, &show_ip_ospf_neighbor_detail_all_cmd_ospfd, sizeof(show_ip_ospf_neighbor_detail_all_cmd_ospfd));
	memcpy(&__activeVars->debug_ospf_packet_send_recv_detail_cmd__X, &debug_ospf_packet_send_recv_detail_cmd_ospfd, sizeof(debug_ospf_packet_send_recv_detail_cmd_ospfd));
	memcpy(&__activeVars->no_ip_ospf_transmit_delay_addr_cmd__X, &no_ip_ospf_transmit_delay_addr_cmd_ospfd, sizeof(no_ip_ospf_transmit_delay_addr_cmd_ospfd));
}

extern struct cmd_element ip_protocol_cmd_zebra;
extern struct cmd_element no_ip_route_mask_distance_cmd_zebra;
extern struct cmd_element no_bandwidth_if_cmd_zebra;
extern struct cmd_element match_ip_address_cmd_zebra;
extern struct cmd_element no_match_interface_val_cmd_zebra;
extern struct cmd_element router_id_cmd_zebra;
extern struct route_map_rule_cmd route_match_ip_next_hop_cmd_zebra;
extern struct cmd_element ip_route_flags_distance2_cmd_zebra;
extern struct route_map_rule_cmd route_match_ip_address_prefix_list_cmd_zebra;
extern struct cmd_element no_ip_route_mask_flags2_cmd_zebra;
extern struct cmd_element ip_route_mask_cmd_zebra;
extern struct cmd_element no_debug_zebra_packet_direct_cmd_zebra;
extern struct cmd_element ip_route_mask_flags_distance_cmd_zebra;
extern struct cmd_element no_ip_route_mask_flags_distance2_cmd_zebra;
extern struct cmd_element show_zebra_client_cmd_zebra;
extern struct cmd_element show_ip_route_supernets_cmd_zebra;
extern struct cmd_element no_multicast_cmd_zebra;
extern struct cmd_element no_ip_forwarding_cmd_zebra;
extern struct cmd_element no_ip_route_distance_cmd_zebra;
extern struct cmd_element no_debug_zebra_packet_cmd_zebra;
extern struct cmd_element no_set_src_val_cmd_zebra;
extern struct cmd_element no_match_interface_cmd_zebra;
extern struct route_map_rule_cmd route_set_src_cmd_zebra;
extern struct cmd_element bandwidth_if_cmd_zebra;
extern struct cmd_element no_ip_route_flags_cmd_zebra;
extern struct cmd_element match_interface_cmd_zebra;
extern struct cmd_element ip_address_cmd_zebra;
extern struct cmd_element show_ip_route_cmd_zebra;
extern struct cmd_element debug_zebra_packet_detail_cmd_zebra;
extern struct cmd_element multicast_cmd_zebra;
extern struct cmd_element show_ip_route_prefix_cmd_zebra;
extern struct cmd_element no_match_ip_address_cmd_zebra;
extern struct cmd_element no_ip_address_label_cmd_zebra;
extern struct cmd_element set_src_cmd_zebra;
extern struct cmd_element show_ip_protocol_cmd_zebra;
extern struct cmd_element zebra_interface_cmd_zebra;
extern struct cmd_element show_interface_desc_cmd_zebra;
extern struct cmd_element ip_forwarding_cmd_zebra;
extern struct cmd_element no_match_ip_address_prefix_list_val_cmd_zebra;
extern struct cmd_element ip_route_flags_distance_cmd_zebra;
extern struct cmd_element show_ip_route_prefix_longer_cmd_zebra;
extern struct cmd_element no_ip_route_mask_flags_cmd_zebra;
extern struct cmd_element no_debug_zebra_kernel_cmd_zebra;
extern struct cmd_element no_ip_route_mask_flags_distance_cmd_zebra;
extern struct cmd_element no_ip_address_cmd_zebra;
extern struct cmd_element no_shutdown_if_cmd_zebra;
extern struct cmd_element no_match_ip_next_hop_cmd_zebra;
extern struct route_map_rule_cmd route_match_ip_address_cmd_zebra;
extern struct cmd_element debug_zebra_kernel_cmd_zebra;
extern struct cmd_element no_ip_route_cmd_zebra;
extern struct cmd_element no_match_ip_next_hop_prefix_list_val_cmd_zebra;
extern struct cmd_element no_set_src_cmd_zebra;
extern struct cmd_element match_ip_next_hop_cmd_zebra;
extern struct route_map_rule_cmd route_match_ip_next_hop_prefix_list_cmd_zebra;
extern struct cmd_element show_debugging_zebra_cmd_zebra;
extern struct cmd_element shutdown_if_cmd_zebra;
extern struct cmd_element no_match_ip_next_hop_prefix_list_cmd_zebra;
extern struct cmd_element no_bandwidth_if_val_cmd_zebra;
extern struct cmd_element ip_route_flags_cmd_zebra;
extern struct cmd_element show_ip_route_summary_cmd_zebra;
extern struct cmd_element no_match_ip_address_prefix_list_cmd_zebra;
extern struct cmd_element show_table_cmd_zebra;
extern struct cmd_element ip_route_cmd_zebra;
extern struct cmd_element show_ip_forwarding_cmd_zebra;
extern struct cmd_element debug_zebra_packet_direct_cmd_zebra;
extern struct cmd_element show_ip_route_protocol_cmd_zebra;
extern struct route_map_rule_cmd route_match_interface_cmd_zebra;
extern struct cmd_element config_table_cmd_zebra;
extern struct cmd_element no_linkdetect_cmd_zebra;
extern struct cmd_element no_debug_zebra_rib_cmd_zebra;
extern struct cmd_element no_ip_route_mask_cmd_zebra;
extern struct cmd_element show_interface_cmd_zebra;
extern struct cmd_element show_ip_route_addr_cmd_zebra;
extern struct cmd_element match_ip_next_hop_prefix_list_cmd_zebra;
extern struct cmd_element no_ip_route_flags_distance_cmd_zebra;
extern struct cmd_element no_router_id_cmd_zebra;
extern struct cmd_element match_ip_address_prefix_list_cmd_zebra;
extern struct cmd_element no_match_ip_address_val_cmd_zebra;
extern struct cmd_element no_ip_protocol_cmd_zebra;
extern struct cmd_element ip_route_mask_flags2_cmd_zebra;
extern struct cmd_element debug_zebra_events_cmd_zebra;
extern struct cmd_element ip_route_mask_distance_cmd_zebra;
extern struct cmd_element no_debug_zebra_events_cmd_zebra;
extern struct cmd_element ip_route_flags2_cmd_zebra;
extern struct cmd_element ip_route_mask_flags_cmd_zebra;
extern struct cmd_element no_debug_zebra_rib_q_cmd_zebra;
extern struct cmd_element no_ip_route_flags2_cmd_zebra;
extern struct cmd_element linkdetect_cmd_zebra;
extern struct cmd_element ip_route_mask_flags_distance2_cmd_zebra;
extern struct cmd_element debug_zebra_rib_q_cmd_zebra;
extern struct cmd_element debug_zebra_packet_cmd_zebra;
extern struct cmd_element no_match_ip_next_hop_val_cmd_zebra;
extern struct cmd_element ip_address_label_cmd_zebra;
extern struct cmd_element debug_zebra_rib_cmd_zebra;
extern struct cmd_element no_ip_route_flags_distance2_cmd_zebra;
extern struct cmd_element ip_route_distance_cmd_zebra;

void GlobalVars_initializeActiveSet_zebra()
{
	struct cmd_node table_node__T = 
{
  TABLE_NODE,
  "",				
  1
};
	struct cmd_node forwarding_node__T = 
{
  FORWARDING_NODE,
  "",				
  1
};
	struct cmd_node debug_node__T = 
{
  DEBUG_NODE,
  "",				
  1
};
	struct zebra_t zebrad__T = 
{
  NULL,
  NULL,
  0
};
	struct cmd_node protocol_node__T =  { PROTOCOL_NODE, "", 1 };
	struct nlsock netlink_cmd__T =  { -1, 0, {0}, "netlink-cmd"};
	struct cmd_node ip_node__T =  { IP_NODE,  "",  1 };
	struct cmd_node interface_node__T = 
{
  INTERFACE_NODE,
  "%s(config-if)# ",
  1
};
	struct nlsock netlink__T =  { -1, 0, {0}, "n""etlink-listen"};
	__activeVars->retain_mode__X =  0;
	memcpy(&__activeVars->ip_protocol_cmd__X, &ip_protocol_cmd_zebra, sizeof(ip_protocol_cmd_zebra));
	memcpy(&__activeVars->no_ip_route_mask_distance_cmd__X, &no_ip_route_mask_distance_cmd_zebra, sizeof(no_ip_route_mask_distance_cmd_zebra));
	memcpy(&__activeVars->no_bandwidth_if_cmd__X, &no_bandwidth_if_cmd_zebra, sizeof(no_bandwidth_if_cmd_zebra));
	memcpy(&__activeVars->match_ip_address_cmd__X, &match_ip_address_cmd_zebra, sizeof(match_ip_address_cmd_zebra));
	memcpy(&__activeVars->no_match_interface_val_cmd__X, &no_match_interface_val_cmd_zebra, sizeof(no_match_interface_val_cmd_zebra));
	memcpy(&__activeVars->router_id_cmd__X, &router_id_cmd_zebra, sizeof(router_id_cmd_zebra));
	memcpy(&__activeVars->route_match_ip_next_hop_cmd__X, &route_match_ip_next_hop_cmd_zebra, sizeof(route_match_ip_next_hop_cmd_zebra));
	memcpy(&__activeVars->ip_route_flags_distance2_cmd__X, &ip_route_flags_distance2_cmd_zebra, sizeof(ip_route_flags_distance2_cmd_zebra));
	__activeVars->pid_file__X =  PATH_ZEBRA_PID;
	memcpy(&__activeVars->route_match_ip_address_prefix_list_cmd__X, &route_match_ip_address_prefix_list_cmd_zebra, sizeof(route_match_ip_address_prefix_list_cmd_zebra));
	memcpy(&__activeVars->table_node__X, &table_node__T, sizeof(table_node__T));
	memcpy(&__activeVars->no_ip_route_mask_flags2_cmd__X, &no_ip_route_mask_flags2_cmd_zebra, sizeof(no_ip_route_mask_flags2_cmd_zebra));
	memcpy(&__activeVars->ip_route_mask_cmd__X, &ip_route_mask_cmd_zebra, sizeof(ip_route_mask_cmd_zebra));
	memcpy(&__activeVars->no_debug_zebra_packet_direct_cmd__X, &no_debug_zebra_packet_direct_cmd_zebra, sizeof(no_debug_zebra_packet_direct_cmd_zebra));
	memcpy(&__activeVars->ip_route_mask_flags_distance_cmd__X, &ip_route_mask_flags_distance_cmd_zebra, sizeof(ip_route_mask_flags_distance_cmd_zebra));
	memcpy(&__activeVars->no_ip_route_mask_flags_distance2_cmd__X, &no_ip_route_mask_flags_distance2_cmd_zebra, sizeof(no_ip_route_mask_flags_distance2_cmd_zebra));
	memcpy(&__activeVars->show_zebra_client_cmd__X, &show_zebra_client_cmd_zebra, sizeof(show_zebra_client_cmd_zebra));
	memcpy(&__activeVars->show_ip_route_supernets_cmd__X, &show_ip_route_supernets_cmd_zebra, sizeof(show_ip_route_supernets_cmd_zebra));
	memcpy(&__activeVars->no_multicast_cmd__X, &no_multicast_cmd_zebra, sizeof(no_multicast_cmd_zebra));
	memcpy(&__activeVars->no_ip_forwarding_cmd__X, &no_ip_forwarding_cmd_zebra, sizeof(no_ip_forwarding_cmd_zebra));
	memcpy(&__activeVars->no_ip_route_distance_cmd__X, &no_ip_route_distance_cmd_zebra, sizeof(no_ip_route_distance_cmd_zebra));
	memcpy(&__activeVars->no_debug_zebra_packet_cmd__X, &no_debug_zebra_packet_cmd_zebra, sizeof(no_debug_zebra_packet_cmd_zebra));
	memcpy(&__activeVars->no_set_src_val_cmd__X, &no_set_src_val_cmd_zebra, sizeof(no_set_src_val_cmd_zebra));
	memcpy(&__activeVars->no_match_interface_cmd__X, &no_match_interface_cmd_zebra, sizeof(no_match_interface_cmd_zebra));
	memcpy(&__activeVars->route_set_src_cmd__X, &route_set_src_cmd_zebra, sizeof(route_set_src_cmd_zebra));
	memcpy(&__activeVars->bandwidth_if_cmd__X, &bandwidth_if_cmd_zebra, sizeof(bandwidth_if_cmd_zebra));
	memcpy(&__activeVars->no_ip_route_flags_cmd__X, &no_ip_route_flags_cmd_zebra, sizeof(no_ip_route_flags_cmd_zebra));
	memcpy(&__activeVars->match_interface_cmd__X, &match_interface_cmd_zebra, sizeof(match_interface_cmd_zebra));
	memcpy(&__activeVars->ip_address_cmd__X, &ip_address_cmd_zebra, sizeof(ip_address_cmd_zebra));
	memcpy(&__activeVars->show_ip_route_cmd__X, &show_ip_route_cmd_zebra, sizeof(show_ip_route_cmd_zebra));
	memcpy(&__activeVars->debug_zebra_packet_detail_cmd__X, &debug_zebra_packet_detail_cmd_zebra, sizeof(debug_zebra_packet_detail_cmd_zebra));
	memcpy(&__activeVars->multicast_cmd__X, &multicast_cmd_zebra, sizeof(multicast_cmd_zebra));
	memcpy(&__activeVars->show_ip_route_prefix_cmd__X, &show_ip_route_prefix_cmd_zebra, sizeof(show_ip_route_prefix_cmd_zebra));
	memcpy(&__activeVars->no_match_ip_address_cmd__X, &no_match_ip_address_cmd_zebra, sizeof(no_match_ip_address_cmd_zebra));
	memcpy(&__activeVars->no_ip_address_label_cmd__X, &no_ip_address_label_cmd_zebra, sizeof(no_ip_address_label_cmd_zebra));
	memcpy(&__activeVars->set_src_cmd__X, &set_src_cmd_zebra, sizeof(set_src_cmd_zebra));
	memcpy(&__activeVars->forwarding_node__X, &forwarding_node__T, sizeof(forwarding_node__T));
	memcpy(&__activeVars->show_ip_protocol_cmd__X, &show_ip_protocol_cmd_zebra, sizeof(show_ip_protocol_cmd_zebra));
	memcpy(&__activeVars->zebra_interface_cmd__X, &zebra_interface_cmd_zebra, sizeof(zebra_interface_cmd_zebra));
	memcpy(&__activeVars->show_interface_desc_cmd__X, &show_interface_desc_cmd_zebra, sizeof(show_interface_desc_cmd_zebra));
	memcpy(&__activeVars->ip_forwarding_cmd__X, &ip_forwarding_cmd_zebra, sizeof(ip_forwarding_cmd_zebra));
	memcpy(&__activeVars->no_match_ip_address_prefix_list_val_cmd__X, &no_match_ip_address_prefix_list_val_cmd_zebra, sizeof(no_match_ip_address_prefix_list_val_cmd_zebra));
	memcpy(&__activeVars->ip_route_flags_distance_cmd__X, &ip_route_flags_distance_cmd_zebra, sizeof(ip_route_flags_distance_cmd_zebra));
	memcpy(&__activeVars->show_ip_route_prefix_longer_cmd__X, &show_ip_route_prefix_longer_cmd_zebra, sizeof(show_ip_route_prefix_longer_cmd_zebra));
	memcpy(&__activeVars->no_ip_route_mask_flags_cmd__X, &no_ip_route_mask_flags_cmd_zebra, sizeof(no_ip_route_mask_flags_cmd_zebra));
	memcpy(&__activeVars->debug_node__X, &debug_node__T, sizeof(debug_node__T));
	memcpy(&__activeVars->no_debug_zebra_kernel_cmd__X, &no_debug_zebra_kernel_cmd_zebra, sizeof(no_debug_zebra_kernel_cmd_zebra));
	memcpy(&__activeVars->no_ip_route_mask_flags_distance_cmd__X, &no_ip_route_mask_flags_distance_cmd_zebra, sizeof(no_ip_route_mask_flags_distance_cmd_zebra));
	memcpy(&__activeVars->no_ip_address_cmd__X, &no_ip_address_cmd_zebra, sizeof(no_ip_address_cmd_zebra));
	memcpy(&__activeVars->no_shutdown_if_cmd__X, &no_shutdown_if_cmd_zebra, sizeof(no_shutdown_if_cmd_zebra));
	memcpy(&__activeVars->no_match_ip_next_hop_cmd__X, &no_match_ip_next_hop_cmd_zebra, sizeof(no_match_ip_next_hop_cmd_zebra));
	memcpy(&__activeVars->route_match_ip_address_cmd__X, &route_match_ip_address_cmd_zebra, sizeof(route_match_ip_address_cmd_zebra));
	memcpy(&__activeVars->zebrad__X, &zebrad__T, sizeof(zebrad__T));
	__activeVars->rib_process_hold_time__X =  10;
	memcpy(&__activeVars->debug_zebra_kernel_cmd__X, &debug_zebra_kernel_cmd_zebra, sizeof(debug_zebra_kernel_cmd_zebra));
	memcpy(&__activeVars->protocol_node__X, &protocol_node__T, sizeof(protocol_node__T));
	memcpy(&__activeVars->no_ip_route_cmd__X, &no_ip_route_cmd_zebra, sizeof(no_ip_route_cmd_zebra));
	memcpy(&__activeVars->no_match_ip_next_hop_prefix_list_val_cmd__X, &no_match_ip_next_hop_prefix_list_val_cmd_zebra, sizeof(no_match_ip_next_hop_prefix_list_val_cmd_zebra));
	memcpy(&__activeVars->no_set_src_cmd__X, &no_set_src_cmd_zebra, sizeof(no_set_src_cmd_zebra));
	memcpy(&__activeVars->match_ip_next_hop_cmd__X, &match_ip_next_hop_cmd_zebra, sizeof(match_ip_next_hop_cmd_zebra));
	memcpy(&__activeVars->route_match_ip_next_hop_prefix_list_cmd__X, &route_match_ip_next_hop_prefix_list_cmd_zebra, sizeof(route_match_ip_next_hop_prefix_list_cmd_zebra));
	memcpy(&__activeVars->netlink_cmd__X, &netlink_cmd__T, sizeof(netlink_cmd__T));
	memcpy(&__activeVars->show_debugging_zebra_cmd__X, &show_debugging_zebra_cmd_zebra, sizeof(show_debugging_zebra_cmd_zebra));
	memcpy(&__activeVars->shutdown_if_cmd__X, &shutdown_if_cmd_zebra, sizeof(shutdown_if_cmd_zebra));
	memcpy(&__activeVars->no_match_ip_next_hop_prefix_list_cmd__X, &no_match_ip_next_hop_prefix_list_cmd_zebra, sizeof(no_match_ip_next_hop_prefix_list_cmd_zebra));
	memcpy(&__activeVars->no_bandwidth_if_val_cmd__X, &no_bandwidth_if_val_cmd_zebra, sizeof(no_bandwidth_if_val_cmd_zebra));
	memcpy(&__activeVars->ip_node__X, &ip_node__T, sizeof(ip_node__T));
	memcpy(&__activeVars->ip_route_flags_cmd__X, &ip_route_flags_cmd_zebra, sizeof(ip_route_flags_cmd_zebra));
	memcpy(&__activeVars->show_ip_route_summary_cmd__X, &show_ip_route_summary_cmd_zebra, sizeof(show_ip_route_summary_cmd_zebra));
	memcpy(&__activeVars->no_match_ip_address_prefix_list_cmd__X, &no_match_ip_address_prefix_list_cmd_zebra, sizeof(no_match_ip_address_prefix_list_cmd_zebra));
	memcpy(&__activeVars->show_table_cmd__X, &show_table_cmd_zebra, sizeof(show_table_cmd_zebra));
	memcpy(&__activeVars->ip_route_cmd__X, &ip_route_cmd_zebra, sizeof(ip_route_cmd_zebra));
	memcpy(&__activeVars->interface_node__X, &interface_node__T, sizeof(interface_node__T));
	memcpy(&__activeVars->show_ip_forwarding_cmd__X, &show_ip_forwarding_cmd_zebra, sizeof(show_ip_forwarding_cmd_zebra));
	memcpy(&__activeVars->debug_zebra_packet_direct_cmd__X, &debug_zebra_packet_direct_cmd_zebra, sizeof(debug_zebra_packet_direct_cmd_zebra));
	memcpy(&__activeVars->show_ip_route_protocol_cmd__X, &show_ip_route_protocol_cmd_zebra, sizeof(show_ip_route_protocol_cmd_zebra));
	memcpy(&__activeVars->route_match_interface_cmd__X, &route_match_interface_cmd_zebra, sizeof(route_match_interface_cmd_zebra));
	memcpy(&__activeVars->config_table_cmd__X, &config_table_cmd_zebra, sizeof(config_table_cmd_zebra));
	memcpy(&__activeVars->no_linkdetect_cmd__X, &no_linkdetect_cmd_zebra, sizeof(no_linkdetect_cmd_zebra));
	memcpy(&__activeVars->no_debug_zebra_rib_cmd__X, &no_debug_zebra_rib_cmd_zebra, sizeof(no_debug_zebra_rib_cmd_zebra));
	memcpy(&__activeVars->no_ip_route_mask_cmd__X, &no_ip_route_mask_cmd_zebra, sizeof(no_ip_route_mask_cmd_zebra));
	memcpy(&__activeVars->netlink__X, &netlink__T, sizeof(netlink__T));
	__activeVars->nl_rcvbufsize__X =  0;
	memcpy(&__activeVars->show_interface_cmd__X, &show_interface_cmd_zebra, sizeof(show_interface_cmd_zebra));
	memcpy(&__activeVars->show_ip_route_addr_cmd__X, &show_ip_route_addr_cmd_zebra, sizeof(show_ip_route_addr_cmd_zebra));
	memcpy(&__activeVars->match_ip_next_hop_prefix_list_cmd__X, &match_ip_next_hop_prefix_list_cmd_zebra, sizeof(match_ip_next_hop_prefix_list_cmd_zebra));
	memcpy(&__activeVars->no_ip_route_flags_distance_cmd__X, &no_ip_route_flags_distance_cmd_zebra, sizeof(no_ip_route_flags_distance_cmd_zebra));
	memcpy(&__activeVars->no_router_id_cmd__X, &no_router_id_cmd_zebra, sizeof(no_router_id_cmd_zebra));
	memcpy(&__activeVars->match_ip_address_prefix_list_cmd__X, &match_ip_address_prefix_list_cmd_zebra, sizeof(match_ip_address_prefix_list_cmd_zebra));
	memcpy(&__activeVars->no_match_ip_address_val_cmd__X, &no_match_ip_address_val_cmd_zebra, sizeof(no_match_ip_address_val_cmd_zebra));
	memcpy(&__activeVars->no_ip_protocol_cmd__X, &no_ip_protocol_cmd_zebra, sizeof(no_ip_protocol_cmd_zebra));
	memcpy(&__activeVars->ip_route_mask_flags2_cmd__X, &ip_route_mask_flags2_cmd_zebra, sizeof(ip_route_mask_flags2_cmd_zebra));
	memcpy(&__activeVars->debug_zebra_events_cmd__X, &debug_zebra_events_cmd_zebra, sizeof(debug_zebra_events_cmd_zebra));
	memcpy(&__activeVars->ip_route_mask_distance_cmd__X, &ip_route_mask_distance_cmd_zebra, sizeof(ip_route_mask_distance_cmd_zebra));
	memcpy(&__activeVars->no_debug_zebra_events_cmd__X, &no_debug_zebra_events_cmd_zebra, sizeof(no_debug_zebra_events_cmd_zebra));
	memcpy(&__activeVars->ip_route_flags2_cmd__X, &ip_route_flags2_cmd_zebra, sizeof(ip_route_flags2_cmd_zebra));
	memcpy(&__activeVars->ip_route_mask_flags_cmd__X, &ip_route_mask_flags_cmd_zebra, sizeof(ip_route_mask_flags_cmd_zebra));
	memcpy(&__activeVars->no_debug_zebra_rib_q_cmd__X, &no_debug_zebra_rib_q_cmd_zebra, sizeof(no_debug_zebra_rib_q_cmd_zebra));
	memcpy(&__activeVars->no_ip_route_flags2_cmd__X, &no_ip_route_flags2_cmd_zebra, sizeof(no_ip_route_flags2_cmd_zebra));
	memcpy(&__activeVars->linkdetect_cmd__X, &linkdetect_cmd_zebra, sizeof(linkdetect_cmd_zebra));
	memcpy(&__activeVars->ip_route_mask_flags_distance2_cmd__X, &ip_route_mask_flags_distance2_cmd_zebra, sizeof(ip_route_mask_flags_distance2_cmd_zebra));
	memcpy(&__activeVars->debug_zebra_rib_q_cmd__X, &debug_zebra_rib_q_cmd_zebra, sizeof(debug_zebra_rib_q_cmd_zebra));
	memcpy(&__activeVars->debug_zebra_packet_cmd__X, &debug_zebra_packet_cmd_zebra, sizeof(debug_zebra_packet_cmd_zebra));
	memcpy(&__activeVars->no_match_ip_next_hop_val_cmd__X, &no_match_ip_next_hop_val_cmd_zebra, sizeof(no_match_ip_next_hop_val_cmd_zebra));
	__activeVars->keep_kernel_mode__X =  0;
	memcpy(&__activeVars->ip_address_label_cmd__X, &ip_address_label_cmd_zebra, sizeof(ip_address_label_cmd_zebra));
	memcpy(&__activeVars->debug_zebra_rib_cmd__X, &debug_zebra_rib_cmd_zebra, sizeof(debug_zebra_rib_cmd_zebra));
	memcpy(&__activeVars->no_ip_route_flags_distance2_cmd__X, &no_ip_route_flags_distance2_cmd_zebra, sizeof(no_ip_route_flags_distance2_cmd_zebra));
	memcpy(&__activeVars->ip_route_distance_cmd__X, &ip_route_distance_cmd_zebra, sizeof(ip_route_distance_cmd_zebra));
}

extern struct cmd_element rmap_show_name_cmd_lib;
extern struct cmd_element no_ip_prefix_list_seq_le_ge_cmd_lib;
extern struct cmd_element no_rmap_onmatch_next_cmd_lib;
extern struct cmd_element show_history_cmd_lib;
extern struct cmd_element show_ip_prefix_list_summary_name_cmd_lib;
extern struct cmd_element enable_password_cmd_lib;
extern struct cmd_element no_terminal_monitor_cmd_lib;
extern struct cmd_element config_terminal_length_cmd_lib;
extern struct cmd_element service_terminal_length_cmd_lib;
extern struct cmd_element accept_lifetime_day_month_day_month_cmd_lib;
extern struct cmd_element config_help_cmd_lib;
extern struct cmd_element vty_login_cmd_lib;
extern struct cmd_element send_lifetime_day_month_month_day_cmd_lib;
extern struct cmd_element no_service_password_encrypt_cmd_lib;
extern struct cmd_element no_service_advanced_vty_cmd_lib;
extern struct cmd_element line_vty_cmd_lib;
extern struct cmd_element no_interface_desc_cmd_lib;
extern struct cmd_element ip_prefix_list_seq_ge_cmd_lib;
extern struct cmd_element no_enable_password_cmd_lib;
extern struct cmd_element key_cmd_lib;
extern struct cmd_element copy_runningconfig_startupconfig_cmd_lib;
extern struct cmd_element no_access_list_extended_any_mask_cmd_lib;
extern struct cmd_element show_memory_ospf_cmd_lib;
extern struct cmd_element no_route_map_cmd_lib;
extern struct cmd_element rmap_onmatch_goto_cmd_lib;
extern struct cmd_element no_access_list_extended_host_any_cmd_lib;
extern struct cmd_element no_access_list_extended_cmd_lib;
extern struct cmd_element no_config_log_record_priority_cmd_lib;
extern struct cmd_element show_memory_lib_cmd_lib;
extern struct cmd_element config_log_syslog_level_cmd_lib;
extern struct cmd_element send_lifetime_infinite_month_day_cmd_lib;
extern struct cmd_element no_config_log_facility_cmd_lib;
extern struct cmd_element show_memory_ripng_cmd_lib;
extern struct cmd_element accept_lifetime_duration_day_month_cmd_lib;
extern struct cmd_element show_memory_zebra_cmd_lib;
extern struct cmd_element send_lifetime_duration_day_month_cmd_lib;
extern struct cmd_element banner_motd_file_cmd_lib;
extern struct cmd_element vty_restricted_mode_cmd_lib;
extern struct cmd_element exec_timeout_min_cmd_lib;
extern struct cmd_element distribute_list_all_cmd_lib;
extern struct cmd_element no_key_string_cmd_lib;
extern struct cmd_element ip_prefix_list_description_cmd_lib;
extern struct cmd_element show_ip_prefix_list_prefix_first_match_cmd_lib;
extern struct cmd_element ip_prefix_list_seq_le_cmd_lib;
extern struct cmd_element send_lifetime_infinite_day_month_cmd_lib;
extern struct cmd_element access_list_extended_host_mask_cmd_lib;
extern struct cmd_element echo_cmd_lib;
extern struct cmd_element accept_lifetime_infinite_day_month_cmd_lib;
extern struct cmd_element access_list_extended_cmd_lib;
extern struct cmd_element show_ip_prefix_list_name_seq_cmd_lib;
extern struct cmd_element no_ip_prefix_list_description_arg_cmd_lib;
extern struct cmd_element show_address_cmd_lib;
extern struct cmd_element ip_prefix_list_ge_le_cmd_lib;
extern struct cmd_element no_distribute_list_all_cmd_lib;
extern struct cmd_element no_key_cmd_lib;
extern struct cmd_element no_route_map_all_cmd_lib;
extern struct cmd_element config_who_cmd_lib;
extern struct cmd_element config_log_syslog_facility_cmd_lib;
extern struct cmd_element no_ip_prefix_list_sequence_number_cmd_lib;
extern struct cmd_element no_access_list_extended_any_host_cmd_lib;
extern struct cmd_element access_list_extended_any_host_cmd_lib;
extern struct cmd_element config_enable_cmd_lib;
extern struct cmd_element no_ip_prefix_list_description_cmd_lib;
extern struct cmd_element no_config_log_syslog_cmd_lib;
extern struct cmd_element no_key_chain_cmd_lib;
extern struct cmd_element terminal_monitor_cmd_lib;
extern struct cmd_element no_config_log_file_level_cmd_lib;
extern struct cmd_element config_log_timestamp_precision_cmd_lib;
extern struct cmd_element access_list_extended_host_any_cmd_lib;
extern struct cmd_element clear_ip_prefix_list_name_prefix_cmd_lib;
extern struct cmd_element config_quit_cmd_lib;
extern struct cmd_element if_rmap_cmd_lib;
extern struct cmd_element show_memory_bgp_cmd_lib;
extern struct cmd_element no_access_list_cmd_lib;
extern struct cmd_element no_ipv6_distribute_list_cmd_lib;
extern struct cmd_element show_memory_all_cmd_lib;
extern struct cmd_element no_distribute_list_prefix_cmd_lib;
extern struct cmd_element no_config_log_timestamp_precision_cmd_lib;
extern struct cmd_element show_memory_ospf6_cmd_lib;
extern struct cmd_element ip_prefix_list_sequence_number_cmd_lib;
extern struct cmd_element config_write_memory_cmd_lib;
extern struct cmd_element config_list_cmd_lib;
extern struct cmd_element vty_no_restricted_mode_cmd_lib;
extern struct cmd_element config_exit_cmd_lib;
extern struct cmd_element interface_cmd_lib;
extern struct cmd_element distribute_list_prefix_all_cmd_lib;
extern struct cmd_element config_log_stdout_level_cmd_lib;
extern struct cmd_element config_log_trap_cmd_lib;
extern struct cmd_element hostname_cmd_lib;
extern struct cmd_element no_distribute_list_prefix_all_cmd_lib;
extern struct cmd_element password_cmd_lib;
extern struct cmd_element no_access_list_extended_any_any_cmd_lib;
extern struct cmd_element no_access_list_all_cmd_lib;
extern struct cmd_element no_access_list_any_cmd_lib;
extern struct cmd_element if_ipv6_rmap_cmd_lib;
extern struct cmd_element no_ip_prefix_list_seq_ge_le_cmd_lib;
extern struct cmd_element config_terminal_no_length_cmd_lib;
extern struct cmd_element ip_prefix_list_seq_le_ge_cmd_lib;
extern struct cmd_element rmap_onmatch_next_cmd_lib;
extern struct cmd_element access_list_extended_mask_any_cmd_lib;
extern struct cmd_element show_memory_rip_cmd_lib;
extern struct cmd_element no_ip_prefix_list_ge_cmd_lib;
extern struct cmd_element access_list_standard_any_cmd_lib;
extern struct cmd_element ip_prefix_list_seq_cmd_lib;
extern struct cmd_element config_log_monitor_cmd_lib;
extern struct cmd_element no_ip_prefix_list_prefix_cmd_lib;
extern struct cmd_element no_ipv6_distribute_list_all_cmd_lib;
extern struct cmd_element rmap_continue_seq_cmd_lib;
extern struct cmd_element interface_desc_cmd_lib;
extern struct cmd_element key_chain_cmd_lib;
extern struct cmd_element ip_prefix_list_ge_cmd_lib;
extern struct cmd_element no_config_log_trap_cmd_lib;
extern struct cmd_element ipv6_distribute_list_prefix_all_cmd_lib;
extern struct cmd_element send_lifetime_day_month_day_month_cmd_lib;
extern struct cmd_element terminal_no_monitor_cmd_lib;
extern struct cmd_element route_map_cmd_lib;
extern struct cmd_element service_password_encrypt_cmd_lib;
extern struct cmd_element config_log_stdout_cmd_lib;
extern struct cmd_element distribute_list_cmd_lib;
extern struct cmd_element no_access_list_standard_nomask_cmd_lib;
extern struct cmd_element clear_ip_prefix_list_cmd_lib;
extern struct cmd_element no_access_list_extended_mask_host_cmd_lib;
extern struct cmd_element no_if_ipv6_rmap_cmd_lib;
extern struct cmd_element access_list_standard_host_cmd_lib;
extern struct cmd_element show_ip_prefix_list_detail_cmd_lib;
extern struct cmd_element no_hostname_cmd_lib;
extern struct cmd_element no_ip_prefix_list_seq_le_cmd_lib;
extern struct cmd_element config_write_cmd_lib;
extern struct cmd_element show_memory_cmd_lib;
extern struct cmd_element config_end_cmd_lib;
extern struct cmd_element no_access_list_remark_arg_cmd_lib;
extern struct cmd_element no_config_log_monitor_cmd_lib;
extern struct cmd_element send_lifetime_month_day_day_month_cmd_lib;
extern struct cmd_element show_ip_prefix_list_name_cmd_lib;
extern struct cmd_element no_banner_motd_cmd_lib;
extern struct cmd_element no_distribute_list_cmd_lib;
extern struct cmd_element rmap_continue_index_cmd_lib;
extern struct cmd_element accept_lifetime_day_month_month_day_cmd_lib;
extern struct cmd_element no_ip_prefix_list_le_ge_cmd_lib;
extern struct cmd_element ip_prefix_list_le_ge_cmd_lib;
extern struct cmd_element ip_prefix_list_cmd_lib;
extern struct cmd_element no_access_list_remark_cmd_lib;
extern struct cmd_element no_interface_cmd_lib;
extern struct cmd_element no_access_list_extended_mask_any_cmd_lib;
extern struct cmd_element ipv6_distribute_list_all_cmd_lib;
extern struct cmd_element show_ip_prefix_list_summary_cmd_lib;
extern struct cmd_element no_if_rmap_cmd_lib;
extern struct cmd_element no_rmap_description_cmd_lib;
extern struct cmd_element no_access_list_standard_host_cmd_lib;
extern struct cmd_element show_ip_access_list_cmd_lib;
extern struct cmd_element rmap_continue_cmd_lib;
extern struct cmd_element exec_timeout_sec_cmd_lib;
extern struct cmd_element config_disable_cmd_lib;
extern struct cmd_element access_list_exact_cmd_lib;
extern struct cmd_element config_log_file_level_cmd_lib;
extern struct cmd_element no_ip_prefix_list_le_cmd_lib;
extern struct cmd_element vty_access_class_cmd_lib;
extern struct cmd_element clear_ip_prefix_list_name_cmd_lib;
extern struct cmd_element ip_prefix_list_seq_ge_le_cmd_lib;
extern struct cmd_element config_write_terminal_cmd_lib;
extern struct cmd_element config_log_file_cmd_lib;
extern struct cmd_element password_text_cmd_lib;
extern struct cmd_element no_access_list_standard_cmd_lib;
extern struct cmd_element send_lifetime_month_day_month_day_cmd_lib;
extern struct cmd_element access_list_extended_host_host_cmd_lib;
extern struct cmd_element no_ip_prefix_list_seq_ge_cmd_lib;
extern struct cmd_element access_list_extended_any_any_cmd_lib;
extern struct cmd_element no_rmap_continue_seq_lib;
extern struct cmd_element no_config_log_syslog_facility_cmd_lib;
extern struct cmd_element config_write_file_cmd_lib;
extern struct cmd_element accept_lifetime_month_day_day_month_cmd_lib;
extern struct cmd_element show_thread_cpu_cmd_lib;
extern struct cmd_element no_exec_timeout_cmd_lib;
extern struct cmd_element show_startup_config_cmd_lib;
extern struct cmd_element no_ip_prefix_list_ge_le_cmd_lib;
extern struct cmd_element config_log_monitor_level_cmd_lib;
extern struct cmd_element no_ipv6_distribute_list_prefix_cmd_lib;
extern struct cmd_element accept_lifetime_infinite_month_day_cmd_lib;
extern struct cmd_element ip_prefix_list_le_cmd_lib;
extern struct cmd_element no_config_log_file_cmd_lib;
extern struct cmd_element no_ipv6_distribute_list_prefix_all_cmd_lib;
extern struct cmd_element show_memory_isis_cmd_lib;
extern struct cmd_element no_vty_login_cmd_lib;
extern struct cmd_element no_service_terminal_length_cmd_lib;
extern struct cmd_element no_access_list_standard_any_cmd_lib;
extern struct cmd_element config_log_facility_cmd_lib;
extern struct cmd_element show_work_queues_cmd_lib;
extern struct cmd_element service_advanced_vty_cmd_lib;
extern struct cmd_element show_running_config_cmd_lib;
extern struct cmd_element no_rmap_call_cmd_lib;
extern struct cmd_element config_terminal_cmd_lib;
extern struct cmd_element banner_motd_default_cmd_lib;
extern struct cmd_element accept_lifetime_duration_month_day_cmd_lib;
extern struct cmd_element no_vty_access_class_cmd_lib;
extern struct cmd_element no_access_list_exact_cmd_lib;
extern struct cmd_element show_ip_prefix_list_cmd_lib;
extern struct cmd_element config_log_record_priority_cmd_lib;
extern struct cmd_element show_version_cmd_lib;
extern struct cmd_element show_ip_prefix_list_prefix_cmd_lib;
extern struct cmd_element enable_password_text_cmd_lib;
extern struct cmd_element show_logging_cmd_lib;
extern struct cmd_element key_string_cmd_lib;
extern struct cmd_element access_list_extended_any_mask_cmd_lib;
extern struct cmd_element access_list_standard_cmd_lib;
extern struct cmd_element rmap_description_cmd_lib;
extern struct cmd_element access_list_extended_mask_host_cmd_lib;
extern struct cmd_element access_list_cmd_lib;
extern struct cmd_element no_config_log_stdout_cmd_lib;
extern struct cmd_element show_ip_access_list_name_cmd_lib;
extern struct cmd_element access_list_any_cmd_lib;
extern struct cmd_element no_ip_prefix_list_cmd_lib;
extern struct cmd_element no_access_list_extended_host_host_cmd_lib;
extern struct cmd_element accept_lifetime_month_day_month_day_cmd_lib;
extern struct cmd_element no_access_list_extended_host_mask_cmd_lib;
extern struct cmd_element access_list_standard_nomask_cmd_lib;
extern struct cmd_element ipv6_distribute_list_cmd_lib;
extern struct cmd_element access_list_remark_cmd_lib;
extern struct cmd_element no_ip_prefix_list_seq_cmd_lib;
extern struct cmd_element ipv6_distribute_list_prefix_cmd_lib;
extern struct cmd_element no_rmap_continue_cmd_lib;
extern struct cmd_element config_logmsg_cmd_lib;
extern struct cmd_element send_lifetime_duration_month_day_cmd_lib;
extern struct cmd_element no_rmap_onmatch_goto_cmd_lib;
extern struct cmd_element show_ip_prefix_list_prefix_longer_cmd_lib;
extern struct cmd_element rmap_call_cmd_lib;
extern struct cmd_element show_ip_prefix_list_detail_name_cmd_lib;
extern struct cmd_element config_log_syslog_cmd_lib;
extern struct cmd_element distribute_list_prefix_cmd_lib;

void GlobalVars_initializeActiveSet_lib()
{
	struct memory_list memory_list_zebra__T[] =  
{
  { MTYPE_RTADV_PREFIX,		"Router Advertisement Prefix"	},
  { MTYPE_VRF,			"VRF"				},
  { MTYPE_VRF_NAME,		"VRF name"			},
  { MTYPE_NEXTHOP,		"Nexthop"			},
  { MTYPE_RIB,			"RIB"				},
  { MTYPE_RIB_QUEUE,		"RIB process work queue"	},
  { MTYPE_STATIC_IPV4,		"Static IPv4 route"		},
  { MTYPE_STATIC_IPV6,		"Static IPv6 route"		},
  { -1, NULL },
};
	struct cmd_node view_node__T = 
{
  VIEW_NODE,
  "%s> ",
};
	struct zebra_desc_table route_types__T[] =  {
  DESC_ENTRY	(ZEBRA_ROUTE_SYSTEM,	"system",	'X' ),
  DESC_ENTRY	(ZEBRA_ROUTE_KERNEL,	"kernel",	'K' ),
  DESC_ENTRY	(ZEBRA_ROUTE_CONNECT,	"connected",	'C' ),
  DESC_ENTRY	(ZEBRA_ROUTE_STATIC,	"static",	'S' ),
  DESC_ENTRY	(ZEBRA_ROUTE_RIP,	"rip",		'R' ),
  DESC_ENTRY	(ZEBRA_ROUTE_RIPNG,	"ripng",	'R' ),
  DESC_ENTRY	(ZEBRA_ROUTE_OSPF,	"ospf",		'O' ),
  DESC_ENTRY	(ZEBRA_ROUTE_OSPF6,	"ospf6",	'O' ),
  DESC_ENTRY	(ZEBRA_ROUTE_ISIS,	"isis",		'I' ),
  DESC_ENTRY	(ZEBRA_ROUTE_BGP,	"bgp",		'B' ),
  DESC_ENTRY	(ZEBRA_ROUTE_HSLS,	"hsls",		'H' ),
};
	struct cmd_node access_node__T = 
{
  ACCESS_NODE,
  "",				
  1
};
	struct prefix_master prefix_master_orf__T =  
{ 
  {NULL, NULL},
  {NULL, NULL},
  1,
  NULL,
  NULL,
};
	struct cmd_node auth_node__T = 
{
  AUTH_NODE,
  "Password: ",
};
	const uint32_t T__T[65] =  {
	0,
	0xd76aa478, 	0xe8c7b756,	0x242070db,	0xc1bdceee,
	0xf57c0faf,	0x4787c62a, 	0xa8304613,	0xfd469501,
	0x698098d8,	0x8b44f7af,	0xffff5bb1,	0x895cd7be,
	0x6b901122, 	0xfd987193, 	0xa679438e,	0x49b40821,

	0xf61e2562,	0xc040b340, 	0x265e5a51, 	0xe9b6c7aa,
	0xd62f105d,	0x2441453,	0xd8a1e681,	0xe7d3fbc8,
	0x21e1cde6,	0xc33707d6, 	0xf4d50d87, 	0x455a14ed,
	0xa9e3e905,	0xfcefa3f8, 	0x676f02d9, 	0x8d2a4c8a,

	0xfffa3942,	0x8771f681, 	0x6d9d6122, 	0xfde5380c,
	0xa4beea44, 	0x4bdecfa9, 	0xf6bb4b60, 	0xbebfbc70,
	0x289b7ec6, 	0xeaa127fa, 	0xd4ef3085,	0x4881d05,
	0xd9d4d039, 	0xe6db99e5, 	0x1fa27cf8, 	0xc4ac5665,

	0xf4292244, 	0x432aff97, 	0xab9423a7, 	0xfc93a039,
	0x655b59c3, 	0x8f0ccc92, 	0xffeff47d, 	0x85845dd1,
	0x6fa87e4f, 	0xfe2ce6e0, 	0xa3014314, 	0x4e0811a1,
	0xf7537e82, 	0xbd3af235, 	0x2ad7d2bb, 	0xeb86d391,
};
	struct cmd_node config_node__T = 
{
  CONFIG_NODE,
  "%s(config)# ",
  1
};
	struct zebra_desc_table unknown__T =  { 0, "unknown", '?' };
	const uint8_t md5_paddat__T[MD5_BUFLEN] =  {
	0x80,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	
};
	struct access_master access_master_ipv4__T =  
{ 
  {NULL, NULL},
  {NULL, NULL},
  NULL,
  NULL,
};
	struct cmd_node vty_node__T = 
{
  VTY_NODE,
  "%s(config-line)# ",
  1,
};
	struct cmd_node enable_node__T = 
{
  ENABLE_NODE,
  "%s# ",
};
	struct cmd_node auth_enable_node__T = 
{
  AUTH_ENABLE_NODE,
  "Password: ",
};
	struct cmd_node prefix_node__T = 
{
  PREFIX_NODE,
  "",				
  1
};
	struct cmd_node keychain_node__T = 
{
  KEYCHAIN_NODE,
  "%s(config-keychain)# ",
  1
};
	struct route_map_list route_map_master__T =  { NULL, NULL, NULL, NULL };
	struct prefix_master prefix_master_ipv4__T =  
{ 
  {NULL, NULL},
  {NULL, NULL},
  1,
  NULL,
  NULL,
};
	struct memory_list memory_list_vtysh__T[] = 
{
  { MTYPE_VTYSH_CONFIG,		"Vtysh configuration",		},
  { MTYPE_VTYSH_CONFIG_LINE,	"Vtysh configuration line"	},
  { -1, NULL },
};
	struct cmd_node keychain_key_node__T = 
{
  KEYCHAIN_KEY_NODE,
  "%s(config-keychain-key)# ",
  1
};
	struct cmd_node rmap_node__T = 
{
  RMAP_NODE,
  "%s(config-route-map)# ",
  1
};
	struct cmd_node restricted_node__T = 
{
  RESTRICTED_NODE,
  "%s$ ",
};
	struct zebra_desc_table command_types__T[] =  {
  DESC_ENTRY	(ZEBRA_INTERFACE_ADD),
  DESC_ENTRY	(ZEBRA_INTERFACE_DELETE),
  DESC_ENTRY	(ZEBRA_INTERFACE_ADDRESS_ADD),
  DESC_ENTRY	(ZEBRA_INTERFACE_ADDRESS_DELETE),
  DESC_ENTRY	(ZEBRA_INTERFACE_UP),
  DESC_ENTRY	(ZEBRA_INTERFACE_DOWN),
  DESC_ENTRY	(ZEBRA_IPV4_ROUTE_ADD),
  DESC_ENTRY	(ZEBRA_IPV4_ROUTE_DELETE),
  DESC_ENTRY	(ZEBRA_IPV6_ROUTE_ADD),
  DESC_ENTRY	(ZEBRA_IPV6_ROUTE_DELETE),
  DESC_ENTRY	(ZEBRA_REDISTRIBUTE_ADD),
  DESC_ENTRY	(ZEBRA_REDISTRIBUTE_DELETE),
  DESC_ENTRY	(ZEBRA_REDISTRIBUTE_DEFAULT_ADD),
  DESC_ENTRY	(ZEBRA_REDISTRIBUTE_DEFAULT_DELETE),
  DESC_ENTRY	(ZEBRA_IPV4_NEXTHOP_LOOKUP),
  DESC_ENTRY	(ZEBRA_IPV6_NEXTHOP_LOOKUP),
  DESC_ENTRY	(ZEBRA_IPV4_IMPORT_LOOKUP),
  DESC_ENTRY	(ZEBRA_IPV6_IMPORT_LOOKUP),
  DESC_ENTRY	(ZEBRA_INTERFACE_RENAME),
  DESC_ENTRY	(ZEBRA_ROUTER_ID_ADD),
  DESC_ENTRY	(ZEBRA_ROUTER_ID_DELETE),
  DESC_ENTRY	(ZEBRA_ROUTER_ID_UPDATE),
};
	memcpy(&__activeVars->rmap_show_name_cmd__X, &rmap_show_name_cmd_lib, sizeof(rmap_show_name_cmd_lib));
	memcpy(&__activeVars->no_ip_prefix_list_seq_le_ge_cmd__X, &no_ip_prefix_list_seq_le_ge_cmd_lib, sizeof(no_ip_prefix_list_seq_le_ge_cmd_lib));
	memcpy(&__activeVars->no_rmap_onmatch_next_cmd__X, &no_rmap_onmatch_next_cmd_lib, sizeof(no_rmap_onmatch_next_cmd_lib));
	memcpy(&__activeVars->show_history_cmd__X, &show_history_cmd_lib, sizeof(show_history_cmd_lib));
	memcpy(&__activeVars->show_ip_prefix_list_summary_name_cmd__X, &show_ip_prefix_list_summary_name_cmd_lib, sizeof(show_ip_prefix_list_summary_name_cmd_lib));
	memcpy(&__activeVars->enable_password_cmd__X, &enable_password_cmd_lib, sizeof(enable_password_cmd_lib));
	memcpy(&__activeVars->memory_list_zebra__X, &memory_list_zebra__T, sizeof(memory_list_zebra__T));
	memcpy(&__activeVars->no_terminal_monitor_cmd__X, &no_terminal_monitor_cmd_lib, sizeof(no_terminal_monitor_cmd_lib));
	memcpy(&__activeVars->config_terminal_length_cmd__X, &config_terminal_length_cmd_lib, sizeof(config_terminal_length_cmd_lib));
	memcpy(&__activeVars->service_terminal_length_cmd__X, &service_terminal_length_cmd_lib, sizeof(service_terminal_length_cmd_lib));
	memcpy(&__activeVars->accept_lifetime_day_month_day_month_cmd__X, &accept_lifetime_day_month_day_month_cmd_lib, sizeof(accept_lifetime_day_month_day_month_cmd_lib));
	memcpy(&__activeVars->config_help_cmd__X, &config_help_cmd_lib, sizeof(config_help_cmd_lib));
	memcpy(&__activeVars->vty_login_cmd__X, &vty_login_cmd_lib, sizeof(vty_login_cmd_lib));
	memcpy(&__activeVars->send_lifetime_day_month_month_day_cmd__X, &send_lifetime_day_month_month_day_cmd_lib, sizeof(send_lifetime_day_month_month_day_cmd_lib));
	__activeVars->logfile_fd__X =  -1;
	__activeVars->cpu_record__X =  NULL;
	memcpy(&__activeVars->no_service_password_encrypt_cmd__X, &no_service_password_encrypt_cmd_lib, sizeof(no_service_password_encrypt_cmd_lib));
	__activeVars->vty_accesslist_name__X =  NULL;
	memcpy(&__activeVars->no_service_advanced_vty_cmd__X, &no_service_advanced_vty_cmd_lib, sizeof(no_service_advanced_vty_cmd_lib));
	memcpy(&__activeVars->line_vty_cmd__X, &line_vty_cmd_lib, sizeof(line_vty_cmd_lib));
	memcpy(&__activeVars->no_interface_desc_cmd__X, &no_interface_desc_cmd_lib, sizeof(no_interface_desc_cmd_lib));
	memcpy(&__activeVars->ip_prefix_list_seq_ge_cmd__X, &ip_prefix_list_seq_ge_cmd_lib, sizeof(ip_prefix_list_seq_ge_cmd_lib));
	memcpy(&__activeVars->no_enable_password_cmd__X, &no_enable_password_cmd_lib, sizeof(no_enable_password_cmd_lib));
	memcpy(&__activeVars->key_cmd__X, &key_cmd_lib, sizeof(key_cmd_lib));
	memcpy(&__activeVars->copy_runningconfig_startupconfig_cmd__X, &copy_runningconfig_startupconfig_cmd_lib, sizeof(copy_runningconfig_startupconfig_cmd_lib));
	memcpy(&__activeVars->no_access_list_extended_any_mask_cmd__X, &no_access_list_extended_any_mask_cmd_lib, sizeof(no_access_list_extended_any_mask_cmd_lib));
	memcpy(&__activeVars->show_memory_ospf_cmd__X, &show_memory_ospf_cmd_lib, sizeof(show_memory_ospf_cmd_lib));
	memcpy(&__activeVars->view_node__X, &view_node__T, sizeof(view_node__T));
	memcpy(&__activeVars->no_route_map_cmd__X, &no_route_map_cmd_lib, sizeof(no_route_map_cmd_lib));
	memcpy(&__activeVars->rmap_onmatch_goto_cmd__X, &rmap_onmatch_goto_cmd_lib, sizeof(rmap_onmatch_goto_cmd_lib));
	memcpy(&__activeVars->no_access_list_extended_host_any_cmd__X, &no_access_list_extended_host_any_cmd_lib, sizeof(no_access_list_extended_host_any_cmd_lib));
	memcpy(&__activeVars->no_access_list_extended_cmd__X, &no_access_list_extended_cmd_lib, sizeof(no_access_list_extended_cmd_lib));
	memcpy(&__activeVars->no_config_log_record_priority_cmd__X, &no_config_log_record_priority_cmd_lib, sizeof(no_config_log_record_priority_cmd_lib));
	__activeVars->__getopt_initialized__X =  0;
	memcpy(&__activeVars->show_memory_lib_cmd__X, &show_memory_lib_cmd_lib, sizeof(show_memory_lib_cmd_lib));
	__activeVars->optind__X =  1;
	memcpy(&__activeVars->config_log_syslog_level_cmd__X, &config_log_syslog_level_cmd_lib, sizeof(config_log_syslog_level_cmd_lib));
	memcpy(&__activeVars->send_lifetime_infinite_month_day_cmd__X, &send_lifetime_infinite_month_day_cmd_lib, sizeof(send_lifetime_infinite_month_day_cmd_lib));
	memcpy(&__activeVars->no_config_log_facility_cmd__X, &no_config_log_facility_cmd_lib, sizeof(no_config_log_facility_cmd_lib));
	memcpy(&__activeVars->show_memory_ripng_cmd__X, &show_memory_ripng_cmd_lib, sizeof(show_memory_ripng_cmd_lib));
	memcpy(&__activeVars->accept_lifetime_duration_day_month_cmd__X, &accept_lifetime_duration_day_month_cmd_lib, sizeof(accept_lifetime_duration_day_month_cmd_lib));
	memcpy(&__activeVars->show_memory_zebra_cmd__X, &show_memory_zebra_cmd_lib, sizeof(show_memory_zebra_cmd_lib));
	memcpy(&__activeVars->send_lifetime_duration_day_month_cmd__X, &send_lifetime_duration_day_month_cmd_lib, sizeof(send_lifetime_duration_day_month_cmd_lib));
	memcpy(&__activeVars->banner_motd_file_cmd__X, &banner_motd_file_cmd_lib, sizeof(banner_motd_file_cmd_lib));
	memcpy(&__activeVars->vty_restricted_mode_cmd__X, &vty_restricted_mode_cmd_lib, sizeof(vty_restricted_mode_cmd_lib));
	memcpy(&__activeVars->exec_timeout_min_cmd__X, &exec_timeout_min_cmd_lib, sizeof(exec_timeout_min_cmd_lib));
	memcpy(&__activeVars->distribute_list_all_cmd__X, &distribute_list_all_cmd_lib, sizeof(distribute_list_all_cmd_lib));
	memcpy(&__activeVars->no_key_string_cmd__X, &no_key_string_cmd_lib, sizeof(no_key_string_cmd_lib));
	__activeVars->opterr__X =  1;
	memcpy(&__activeVars->ip_prefix_list_description_cmd__X, &ip_prefix_list_description_cmd_lib, sizeof(ip_prefix_list_description_cmd_lib));
	memcpy(&__activeVars->show_ip_prefix_list_prefix_first_match_cmd__X, &show_ip_prefix_list_prefix_first_match_cmd_lib, sizeof(show_ip_prefix_list_prefix_first_match_cmd_lib));
	__activeVars->telnet_space_char__X =  ' ';
	memcpy(&__activeVars->ip_prefix_list_seq_le_cmd__X, &ip_prefix_list_seq_le_cmd_lib, sizeof(ip_prefix_list_seq_le_cmd_lib));
	memcpy(&__activeVars->send_lifetime_infinite_day_month_cmd__X, &send_lifetime_infinite_day_month_cmd_lib, sizeof(send_lifetime_infinite_day_month_cmd_lib));
	memcpy(&__activeVars->access_list_extended_host_mask_cmd__X, &access_list_extended_host_mask_cmd_lib, sizeof(access_list_extended_host_mask_cmd_lib));
	memcpy(&__activeVars->echo_cmd__X, &echo_cmd_lib, sizeof(echo_cmd_lib));
	memcpy(&__activeVars->accept_lifetime_infinite_day_month_cmd__X, &accept_lifetime_infinite_day_month_cmd_lib, sizeof(accept_lifetime_infinite_day_month_cmd_lib));
	memcpy(&__activeVars->access_list_extended_cmd__X, &access_list_extended_cmd_lib, sizeof(access_list_extended_cmd_lib));
	memcpy(&__activeVars->show_ip_prefix_list_name_seq_cmd__X, &show_ip_prefix_list_name_seq_cmd_lib, sizeof(show_ip_prefix_list_name_seq_cmd_lib));
	memcpy(&__activeVars->no_ip_prefix_list_description_arg_cmd__X, &no_ip_prefix_list_description_arg_cmd_lib, sizeof(no_ip_prefix_list_description_arg_cmd_lib));
	memcpy(&__activeVars->show_address_cmd__X, &show_address_cmd_lib, sizeof(show_address_cmd_lib));
	memcpy(&__activeVars->ip_prefix_list_ge_le_cmd__X, &ip_prefix_list_ge_le_cmd_lib, sizeof(ip_prefix_list_ge_le_cmd_lib));
	memcpy(&__activeVars->no_distribute_list_all_cmd__X, &no_distribute_list_all_cmd_lib, sizeof(no_distribute_list_all_cmd_lib));
	memcpy(&__activeVars->no_key_cmd__X, &no_key_cmd_lib, sizeof(no_key_cmd_lib));
	memcpy(&__activeVars->no_route_map_all_cmd__X, &no_route_map_all_cmd_lib, sizeof(no_route_map_all_cmd_lib));
	memcpy(&__activeVars->config_who_cmd__X, &config_who_cmd_lib, sizeof(config_who_cmd_lib));
	memcpy(&__activeVars->config_log_syslog_facility_cmd__X, &config_log_syslog_facility_cmd_lib, sizeof(config_log_syslog_facility_cmd_lib));
	__activeVars->optopt__X =  '?';
	memcpy(&__activeVars->route_types__X, &route_types__T, sizeof(route_types__T));
	memcpy(&__activeVars->no_ip_prefix_list_sequence_number_cmd__X, &no_ip_prefix_list_sequence_number_cmd_lib, sizeof(no_ip_prefix_list_sequence_number_cmd_lib));
	memcpy(&__activeVars->no_access_list_extended_any_host_cmd__X, &no_access_list_extended_any_host_cmd_lib, sizeof(no_access_list_extended_any_host_cmd_lib));
	memcpy(&__activeVars->access_node__X, &access_node__T, sizeof(access_node__T));
	memcpy(&__activeVars->access_list_extended_any_host_cmd__X, &access_list_extended_any_host_cmd_lib, sizeof(access_list_extended_any_host_cmd_lib));
	memcpy(&__activeVars->config_enable_cmd__X, &config_enable_cmd_lib, sizeof(config_enable_cmd_lib));
	memcpy(&__activeVars->no_ip_prefix_list_description_cmd__X, &no_ip_prefix_list_description_cmd_lib, sizeof(no_ip_prefix_list_description_cmd_lib));
	memcpy(&__activeVars->no_config_log_syslog_cmd__X, &no_config_log_syslog_cmd_lib, sizeof(no_config_log_syslog_cmd_lib));
	memcpy(&__activeVars->no_key_chain_cmd__X, &no_key_chain_cmd_lib, sizeof(no_key_chain_cmd_lib));
	memcpy(&__activeVars->terminal_monitor_cmd__X, &terminal_monitor_cmd_lib, sizeof(terminal_monitor_cmd_lib));
	memcpy(&__activeVars->no_config_log_file_level_cmd__X, &no_config_log_file_level_cmd_lib, sizeof(no_config_log_file_level_cmd_lib));
	memcpy(&__activeVars->config_log_timestamp_precision_cmd__X, &config_log_timestamp_precision_cmd_lib, sizeof(config_log_timestamp_precision_cmd_lib));
	memcpy(&__activeVars->access_list_extended_host_any_cmd__X, &access_list_extended_host_any_cmd_lib, sizeof(access_list_extended_host_any_cmd_lib));
	memcpy(&__activeVars->clear_ip_prefix_list_name_prefix_cmd__X, &clear_ip_prefix_list_name_prefix_cmd_lib, sizeof(clear_ip_prefix_list_name_prefix_cmd_lib));
	__activeVars->optarg__X =  NULL;
	memcpy(&__activeVars->config_quit_cmd__X, &config_quit_cmd_lib, sizeof(config_quit_cmd_lib));
	memcpy(&__activeVars->if_rmap_cmd__X, &if_rmap_cmd_lib, sizeof(if_rmap_cmd_lib));
	memcpy(&__activeVars->prefix_master_orf__X, &prefix_master_orf__T, sizeof(prefix_master_orf__T));
	memcpy(&__activeVars->auth_node__X, &auth_node__T, sizeof(auth_node__T));
	memcpy(&__activeVars->show_memory_bgp_cmd__X, &show_memory_bgp_cmd_lib, sizeof(show_memory_bgp_cmd_lib));
	memcpy(&__activeVars->no_access_list_cmd__X, &no_access_list_cmd_lib, sizeof(no_access_list_cmd_lib));
	memcpy(&__activeVars->no_ipv6_distribute_list_cmd__X, &no_ipv6_distribute_list_cmd_lib, sizeof(no_ipv6_distribute_list_cmd_lib));
	__activeVars->cmdvec__X =  NULL;
	memcpy(&__activeVars->show_memory_all_cmd__X, &show_memory_all_cmd_lib, sizeof(show_memory_all_cmd_lib));
	memcpy(&__activeVars->no_distribute_list_prefix_cmd__X, &no_distribute_list_prefix_cmd_lib, sizeof(no_distribute_list_prefix_cmd_lib));
	__activeVars->zclient_debug__X =  0;
	memcpy(&__activeVars->no_config_log_timestamp_precision_cmd__X, &no_config_log_timestamp_precision_cmd_lib, sizeof(no_config_log_timestamp_precision_cmd_lib));
	memcpy(&__activeVars->show_memory_ospf6_cmd__X, &show_memory_ospf6_cmd_lib, sizeof(show_memory_ospf6_cmd_lib));
	memcpy(&__activeVars->ip_prefix_list_sequence_number_cmd__X, &ip_prefix_list_sequence_number_cmd_lib, sizeof(ip_prefix_list_sequence_number_cmd_lib));
	memcpy(&__activeVars->config_write_memory_cmd__X, &config_write_memory_cmd_lib, sizeof(config_write_memory_cmd_lib));
	memcpy(&__activeVars->T__X, &T__T, sizeof(T__T));
	memcpy(&__activeVars->config_list_cmd__X, &config_list_cmd_lib, sizeof(config_list_cmd_lib));
	memcpy(&__activeVars->vty_no_restricted_mode_cmd__X, &vty_no_restricted_mode_cmd_lib, sizeof(vty_no_restricted_mode_cmd_lib));
	memcpy(&__activeVars->config_exit_cmd__X, &config_exit_cmd_lib, sizeof(config_exit_cmd_lib));
	__activeVars->restricted_mode__X =  0;
	memcpy(&__activeVars->interface_cmd__X, &interface_cmd_lib, sizeof(interface_cmd_lib));
	memcpy(&__activeVars->distribute_list_prefix_all_cmd__X, &distribute_list_prefix_all_cmd_lib, sizeof(distribute_list_prefix_all_cmd_lib));
	memcpy(&__activeVars->config_log_stdout_level_cmd__X, &config_log_stdout_level_cmd_lib, sizeof(config_log_stdout_level_cmd_lib));
	memcpy(&__activeVars->config_log_trap_cmd__X, &config_log_trap_cmd_lib, sizeof(config_log_trap_cmd_lib));
	memcpy(&__activeVars->hostname_cmd__X, &hostname_cmd_lib, sizeof(hostname_cmd_lib));
	memcpy(&__activeVars->no_distribute_list_prefix_all_cmd__X, &no_distribute_list_prefix_all_cmd_lib, sizeof(no_distribute_list_prefix_all_cmd_lib));
	memcpy(&__activeVars->password_cmd__X, &password_cmd_lib, sizeof(password_cmd_lib));
	memcpy(&__activeVars->no_access_list_extended_any_any_cmd__X, &no_access_list_extended_any_any_cmd_lib, sizeof(no_access_list_extended_any_any_cmd_lib));
	memcpy(&__activeVars->no_access_list_all_cmd__X, &no_access_list_all_cmd_lib, sizeof(no_access_list_all_cmd_lib));
	memcpy(&__activeVars->no_access_list_any_cmd__X, &no_access_list_any_cmd_lib, sizeof(no_access_list_any_cmd_lib));
	memcpy(&__activeVars->if_ipv6_rmap_cmd__X, &if_ipv6_rmap_cmd_lib, sizeof(if_ipv6_rmap_cmd_lib));
	__activeVars->no_password_check__X =  0;
	memcpy(&__activeVars->no_ip_prefix_list_seq_ge_le_cmd__X, &no_ip_prefix_list_seq_ge_le_cmd_lib, sizeof(no_ip_prefix_list_seq_ge_le_cmd_lib));
	memcpy(&__activeVars->config_terminal_no_length_cmd__X, &config_terminal_no_length_cmd_lib, sizeof(config_terminal_no_length_cmd_lib));
	memcpy(&__activeVars->ip_prefix_list_seq_le_ge_cmd__X, &ip_prefix_list_seq_le_ge_cmd_lib, sizeof(ip_prefix_list_seq_le_ge_cmd_lib));
	memcpy(&__activeVars->config_node__X, &config_node__T, sizeof(config_node__T));
	memcpy(&__activeVars->unknown__X, &unknown__T, sizeof(unknown__T));
	memcpy(&__activeVars->rmap_onmatch_next_cmd__X, &rmap_onmatch_next_cmd_lib, sizeof(rmap_onmatch_next_cmd_lib));
	memcpy(&__activeVars->access_list_extended_mask_any_cmd__X, &access_list_extended_mask_any_cmd_lib, sizeof(access_list_extended_mask_any_cmd_lib));
	memcpy(&__activeVars->show_memory_rip_cmd__X, &show_memory_rip_cmd_lib, sizeof(show_memory_rip_cmd_lib));
	memcpy(&__activeVars->no_ip_prefix_list_ge_cmd__X, &no_ip_prefix_list_ge_cmd_lib, sizeof(no_ip_prefix_list_ge_cmd_lib));
	__activeVars->zprivs_null_state__X =  ZPRIVS_RAISED;
	memcpy(&__activeVars->access_list_standard_any_cmd__X, &access_list_standard_any_cmd_lib, sizeof(access_list_standard_any_cmd_lib));
	memcpy(&__activeVars->ip_prefix_list_seq_cmd__X, &ip_prefix_list_seq_cmd_lib, sizeof(ip_prefix_list_seq_cmd_lib));
	memcpy(&__activeVars->config_log_monitor_cmd__X, &config_log_monitor_cmd_lib, sizeof(config_log_monitor_cmd_lib));
	memcpy(&__activeVars->no_ip_prefix_list_prefix_cmd__X, &no_ip_prefix_list_prefix_cmd_lib, sizeof(no_ip_prefix_list_prefix_cmd_lib));
	memcpy(&__activeVars->no_ipv6_distribute_list_all_cmd__X, &no_ipv6_distribute_list_all_cmd_lib, sizeof(no_ipv6_distribute_list_all_cmd_lib));
	memcpy(&__activeVars->md5_paddat__X, &md5_paddat__T, sizeof(md5_paddat__T));
	memcpy(&__activeVars->access_master_ipv4__X, &access_master_ipv4__T, sizeof(access_master_ipv4__T));
	__activeVars->if_rmap_delete_hook__X =  NULL;
	memcpy(&__activeVars->vty_node__X, &vty_node__T, sizeof(vty_node__T));
	memcpy(&__activeVars->rmap_continue_seq_cmd__X, &rmap_continue_seq_cmd_lib, sizeof(rmap_continue_seq_cmd_lib));
	memcpy(&__activeVars->enable_node__X, &enable_node__T, sizeof(enable_node__T));
	memcpy(&__activeVars->interface_desc_cmd__X, &interface_desc_cmd_lib, sizeof(interface_desc_cmd_lib));
	__activeVars->re_max_failures__X =  20000;
	memcpy(&__activeVars->key_chain_cmd__X, &key_chain_cmd_lib, sizeof(key_chain_cmd_lib));
	memcpy(&__activeVars->ip_prefix_list_ge_cmd__X, &ip_prefix_list_ge_cmd_lib, sizeof(ip_prefix_list_ge_cmd_lib));
	memcpy(&__activeVars->auth_enable_node__X, &auth_enable_node__T, sizeof(auth_enable_node__T));
	memcpy(&__activeVars->no_config_log_trap_cmd__X, &no_config_log_trap_cmd_lib, sizeof(no_config_log_trap_cmd_lib));
	memcpy(&__activeVars->ipv6_distribute_list_prefix_all_cmd__X, &ipv6_distribute_list_prefix_all_cmd_lib, sizeof(ipv6_distribute_list_prefix_all_cmd_lib));
	memcpy(&__activeVars->send_lifetime_day_month_day_month_cmd__X, &send_lifetime_day_month_day_month_cmd_lib, sizeof(send_lifetime_day_month_day_month_cmd_lib));
	memcpy(&__activeVars->terminal_no_monitor_cmd__X, &terminal_no_monitor_cmd_lib, sizeof(terminal_no_monitor_cmd_lib));
	memcpy(&__activeVars->route_map_cmd__X, &route_map_cmd_lib, sizeof(route_map_cmd_lib));
	memcpy(&__activeVars->service_password_encrypt_cmd__X, &service_password_encrypt_cmd_lib, sizeof(service_password_encrypt_cmd_lib));
	memcpy(&__activeVars->config_log_stdout_cmd__X, &config_log_stdout_cmd_lib, sizeof(config_log_stdout_cmd_lib));
	memcpy(&__activeVars->distribute_list_cmd__X, &distribute_list_cmd_lib, sizeof(distribute_list_cmd_lib));
	memcpy(&__activeVars->no_access_list_standard_nomask_cmd__X, &no_access_list_standard_nomask_cmd_lib, sizeof(no_access_list_standard_nomask_cmd_lib));
	memcpy(&__activeVars->clear_ip_prefix_list_cmd__X, &clear_ip_prefix_list_cmd_lib, sizeof(clear_ip_prefix_list_cmd_lib));
	memcpy(&__activeVars->no_access_list_extended_mask_host_cmd__X, &no_access_list_extended_mask_host_cmd_lib, sizeof(no_access_list_extended_mask_host_cmd_lib));
	memcpy(&__activeVars->no_if_ipv6_rmap_cmd__X, &no_if_ipv6_rmap_cmd_lib, sizeof(no_if_ipv6_rmap_cmd_lib));
	memcpy(&__activeVars->access_list_standard_host_cmd__X, &access_list_standard_host_cmd_lib, sizeof(access_list_standard_host_cmd_lib));
	__activeVars->zlog_default__X =  NULL;
	memcpy(&__activeVars->show_ip_prefix_list_detail_cmd__X, &show_ip_prefix_list_detail_cmd_lib, sizeof(show_ip_prefix_list_detail_cmd_lib));
	memcpy(&__activeVars->no_hostname_cmd__X, &no_hostname_cmd_lib, sizeof(no_hostname_cmd_lib));
	memcpy(&__activeVars->no_ip_prefix_list_seq_le_cmd__X, &no_ip_prefix_list_seq_le_cmd_lib, sizeof(no_ip_prefix_list_seq_le_cmd_lib));
	memcpy(&__activeVars->prefix_node__X, &prefix_node__T, sizeof(prefix_node__T));
	memcpy(&__activeVars->config_write_cmd__X, &config_write_cmd_lib, sizeof(config_write_cmd_lib));
	__activeVars->vty_ipv6_accesslist_name__X =  NULL;
	memcpy(&__activeVars->show_memory_cmd__X, &show_memory_cmd_lib, sizeof(show_memory_cmd_lib));
	memcpy(&__activeVars->config_end_cmd__X, &config_end_cmd_lib, sizeof(config_end_cmd_lib));
	memcpy(&__activeVars->keychain_node__X, &keychain_node__T, sizeof(keychain_node__T));
	memcpy(&__activeVars->route_map_master__X, &route_map_master__T, sizeof(route_map_master__T));
	memcpy(&__activeVars->no_access_list_remark_arg_cmd__X, &no_access_list_remark_arg_cmd_lib, sizeof(no_access_list_remark_arg_cmd_lib));
	memcpy(&__activeVars->no_config_log_monitor_cmd__X, &no_config_log_monitor_cmd_lib, sizeof(no_config_log_monitor_cmd_lib));
	memcpy(&__activeVars->send_lifetime_month_day_day_month_cmd__X, &send_lifetime_month_day_day_month_cmd_lib, sizeof(send_lifetime_month_day_day_month_cmd_lib));
	memcpy(&__activeVars->show_ip_prefix_list_name_cmd__X, &show_ip_prefix_list_name_cmd_lib, sizeof(show_ip_prefix_list_name_cmd_lib));
	memcpy(&__activeVars->no_banner_motd_cmd__X, &no_banner_motd_cmd_lib, sizeof(no_banner_motd_cmd_lib));
	memcpy(&__activeVars->no_distribute_list_cmd__X, &no_distribute_list_cmd_lib, sizeof(no_distribute_list_cmd_lib));
	memcpy(&__activeVars->rmap_continue_index_cmd__X, &rmap_continue_index_cmd_lib, sizeof(rmap_continue_index_cmd_lib));
	memcpy(&__activeVars->accept_lifetime_day_month_month_day_cmd__X, &accept_lifetime_day_month_month_day_cmd_lib, sizeof(accept_lifetime_day_month_month_day_cmd_lib));
	memcpy(&__activeVars->no_ip_prefix_list_le_ge_cmd__X, &no_ip_prefix_list_le_ge_cmd_lib, sizeof(no_ip_prefix_list_le_ge_cmd_lib));
	memcpy(&__activeVars->prefix_master_ipv4__X, &prefix_master_ipv4__T, sizeof(prefix_master_ipv4__T));
	memcpy(&__activeVars->ip_prefix_list_le_ge_cmd__X, &ip_prefix_list_le_ge_cmd_lib, sizeof(ip_prefix_list_le_ge_cmd_lib));
	memcpy(&__activeVars->ip_prefix_list_cmd__X, &ip_prefix_list_cmd_lib, sizeof(ip_prefix_list_cmd_lib));
	memcpy(&__activeVars->no_access_list_remark_cmd__X, &no_access_list_remark_cmd_lib, sizeof(no_access_list_remark_cmd_lib));
	memcpy(&__activeVars->no_interface_cmd__X, &no_interface_cmd_lib, sizeof(no_interface_cmd_lib));
	memcpy(&__activeVars->no_access_list_extended_mask_any_cmd__X, &no_access_list_extended_mask_any_cmd_lib, sizeof(no_access_list_extended_mask_any_cmd_lib));
	memcpy(&__activeVars->ipv6_distribute_list_all_cmd__X, &ipv6_distribute_list_all_cmd_lib, sizeof(ipv6_distribute_list_all_cmd_lib));
	memcpy(&__activeVars->show_ip_prefix_list_summary_cmd__X, &show_ip_prefix_list_summary_cmd_lib, sizeof(show_ip_prefix_list_summary_cmd_lib));
	memcpy(&__activeVars->no_if_rmap_cmd__X, &no_if_rmap_cmd_lib, sizeof(no_if_rmap_cmd_lib));
	memcpy(&__activeVars->no_rmap_description_cmd__X, &no_rmap_description_cmd_lib, sizeof(no_rmap_description_cmd_lib));
	memcpy(&__activeVars->no_access_list_standard_host_cmd__X, &no_access_list_standard_host_cmd_lib, sizeof(no_access_list_standard_host_cmd_lib));
	memcpy(&__activeVars->memory_list_vtysh__X, &memory_list_vtysh__T, sizeof(memory_list_vtysh__T));
	memcpy(&__activeVars->show_ip_access_list_cmd__X, &show_ip_access_list_cmd_lib, sizeof(show_ip_access_list_cmd_lib));
	memcpy(&__activeVars->rmap_continue_cmd__X, &rmap_continue_cmd_lib, sizeof(rmap_continue_cmd_lib));
	memcpy(&__activeVars->exec_timeout_sec_cmd__X, &exec_timeout_sec_cmd_lib, sizeof(exec_timeout_sec_cmd_lib));
	memcpy(&__activeVars->config_disable_cmd__X, &config_disable_cmd_lib, sizeof(config_disable_cmd_lib));
	memcpy(&__activeVars->access_list_exact_cmd__X, &access_list_exact_cmd_lib, sizeof(access_list_exact_cmd_lib));
	memcpy(&__activeVars->config_log_file_level_cmd__X, &config_log_file_level_cmd_lib, sizeof(config_log_file_level_cmd_lib));
	memcpy(&__activeVars->no_ip_prefix_list_le_cmd__X, &no_ip_prefix_list_le_cmd_lib, sizeof(no_ip_prefix_list_le_cmd_lib));
	memcpy(&__activeVars->vty_access_class_cmd__X, &vty_access_class_cmd_lib, sizeof(vty_access_class_cmd_lib));
	memcpy(&__activeVars->clear_ip_prefix_list_name_cmd__X, &clear_ip_prefix_list_name_cmd_lib, sizeof(clear_ip_prefix_list_name_cmd_lib));
	memcpy(&__activeVars->ip_prefix_list_seq_ge_le_cmd__X, &ip_prefix_list_seq_ge_le_cmd_lib, sizeof(ip_prefix_list_seq_ge_le_cmd_lib));
	memcpy(&__activeVars->config_write_terminal_cmd__X, &config_write_terminal_cmd_lib, sizeof(config_write_terminal_cmd_lib));
	memcpy(&__activeVars->config_log_file_cmd__X, &config_log_file_cmd_lib, sizeof(config_log_file_cmd_lib));
	memcpy(&__activeVars->password_text_cmd__X, &password_text_cmd_lib, sizeof(password_text_cmd_lib));
	memcpy(&__activeVars->no_access_list_standard_cmd__X, &no_access_list_standard_cmd_lib, sizeof(no_access_list_standard_cmd_lib));
	memcpy(&__activeVars->send_lifetime_month_day_month_day_cmd__X, &send_lifetime_month_day_month_day_cmd_lib, sizeof(send_lifetime_month_day_month_day_cmd_lib));
	memcpy(&__activeVars->keychain_key_node__X, &keychain_key_node__T, sizeof(keychain_key_node__T));
	memcpy(&__activeVars->access_list_extended_host_host_cmd__X, &access_list_extended_host_host_cmd_lib, sizeof(access_list_extended_host_host_cmd_lib));
	memcpy(&__activeVars->no_ip_prefix_list_seq_ge_cmd__X, &no_ip_prefix_list_seq_ge_cmd_lib, sizeof(no_ip_prefix_list_seq_ge_cmd_lib));
	memcpy(&__activeVars->access_list_extended_any_any_cmd__X, &access_list_extended_any_any_cmd_lib, sizeof(access_list_extended_any_any_cmd_lib));
	memcpy(&__activeVars->no_rmap_continue_seq__X, &no_rmap_continue_seq_lib, sizeof(no_rmap_continue_seq_lib));
	memcpy(&__activeVars->no_config_log_syslog_facility_cmd__X, &no_config_log_syslog_facility_cmd_lib, sizeof(no_config_log_syslog_facility_cmd_lib));
	memcpy(&__activeVars->config_write_file_cmd__X, &config_write_file_cmd_lib, sizeof(config_write_file_cmd_lib));
	memcpy(&__activeVars->accept_lifetime_month_day_day_month_cmd__X, &accept_lifetime_month_day_day_month_cmd_lib, sizeof(accept_lifetime_month_day_day_month_cmd_lib));
	__activeVars->vty_timeout_val__X =  VTY_TIMEOUT_DEFAULT;
	memcpy(&__activeVars->rmap_node__X, &rmap_node__T, sizeof(rmap_node__T));
	memcpy(&__activeVars->show_thread_cpu_cmd__X, &show_thread_cpu_cmd_lib, sizeof(show_thread_cpu_cmd_lib));
	memcpy(&__activeVars->no_exec_timeout_cmd__X, &no_exec_timeout_cmd_lib, sizeof(no_exec_timeout_cmd_lib));
	memcpy(&__activeVars->show_startup_config_cmd__X, &show_startup_config_cmd_lib, sizeof(show_startup_config_cmd_lib));
	memcpy(&__activeVars->no_ip_prefix_list_ge_le_cmd__X, &no_ip_prefix_list_ge_le_cmd_lib, sizeof(no_ip_prefix_list_ge_le_cmd_lib));
	memcpy(&__activeVars->config_log_monitor_level_cmd__X, &config_log_monitor_level_cmd_lib, sizeof(config_log_monitor_level_cmd_lib));
	memcpy(&__activeVars->no_ipv6_distribute_list_prefix_cmd__X, &no_ipv6_distribute_list_prefix_cmd_lib, sizeof(no_ipv6_distribute_list_prefix_cmd_lib));
	memcpy(&__activeVars->accept_lifetime_infinite_month_day_cmd__X, &accept_lifetime_infinite_month_day_cmd_lib, sizeof(accept_lifetime_infinite_month_day_cmd_lib));
	memcpy(&__activeVars->ip_prefix_list_le_cmd__X, &ip_prefix_list_le_cmd_lib, sizeof(ip_prefix_list_le_cmd_lib));
	memcpy(&__activeVars->no_config_log_file_cmd__X, &no_config_log_file_cmd_lib, sizeof(no_config_log_file_cmd_lib));
	memcpy(&__activeVars->no_ipv6_distribute_list_prefix_all_cmd__X, &no_ipv6_distribute_list_prefix_all_cmd_lib, sizeof(no_ipv6_distribute_list_prefix_all_cmd_lib));
	__activeVars->if_rmap_add_hook__X =  NULL;
	memcpy(&__activeVars->show_memory_isis_cmd__X, &show_memory_isis_cmd_lib, sizeof(show_memory_isis_cmd_lib));
	memcpy(&__activeVars->no_vty_login_cmd__X, &no_vty_login_cmd_lib, sizeof(no_vty_login_cmd_lib));
	memcpy(&__activeVars->no_service_terminal_length_cmd__X, &no_service_terminal_length_cmd_lib, sizeof(no_service_terminal_length_cmd_lib));
	memcpy(&__activeVars->no_access_list_standard_any_cmd__X, &no_access_list_standard_any_cmd_lib, sizeof(no_access_list_standard_any_cmd_lib));
	memcpy(&__activeVars->config_log_facility_cmd__X, &config_log_facility_cmd_lib, sizeof(config_log_facility_cmd_lib));
	memcpy(&__activeVars->show_work_queues_cmd__X, &show_work_queues_cmd_lib, sizeof(show_work_queues_cmd_lib));
	memcpy(&__activeVars->service_advanced_vty_cmd__X, &service_advanced_vty_cmd_lib, sizeof(service_advanced_vty_cmd_lib));
	memcpy(&__activeVars->show_running_config_cmd__X, &show_running_config_cmd_lib, sizeof(show_running_config_cmd_lib));
	memcpy(&__activeVars->restricted_node__X, &restricted_node__T, sizeof(restricted_node__T));
	memcpy(&__activeVars->no_rmap_call_cmd__X, &no_rmap_call_cmd_lib, sizeof(no_rmap_call_cmd_lib));
	memcpy(&__activeVars->config_terminal_cmd__X, &config_terminal_cmd_lib, sizeof(config_terminal_cmd_lib));
	__activeVars->restricted_mode_default__X =  0;
	memcpy(&__activeVars->banner_motd_default_cmd__X, &banner_motd_default_cmd_lib, sizeof(banner_motd_default_cmd_lib));
	memcpy(&__activeVars->accept_lifetime_duration_month_day_cmd__X, &accept_lifetime_duration_month_day_cmd_lib, sizeof(accept_lifetime_duration_month_day_cmd_lib));
	memcpy(&__activeVars->no_vty_access_class_cmd__X, &no_vty_access_class_cmd_lib, sizeof(no_vty_access_class_cmd_lib));
	memcpy(&__activeVars->no_access_list_exact_cmd__X, &no_access_list_exact_cmd_lib, sizeof(no_access_list_exact_cmd_lib));
	memcpy(&__activeVars->show_ip_prefix_list_cmd__X, &show_ip_prefix_list_cmd_lib, sizeof(show_ip_prefix_list_cmd_lib));
	memcpy(&__activeVars->config_log_record_priority_cmd__X, &config_log_record_priority_cmd_lib, sizeof(config_log_record_priority_cmd_lib));
	memcpy(&__activeVars->show_version_cmd__X, &show_version_cmd_lib, sizeof(show_version_cmd_lib));
	memcpy(&__activeVars->show_ip_prefix_list_prefix_cmd__X, &show_ip_prefix_list_prefix_cmd_lib, sizeof(show_ip_prefix_list_prefix_cmd_lib));
	memcpy(&__activeVars->enable_password_text_cmd__X, &enable_password_text_cmd_lib, sizeof(enable_password_text_cmd_lib));
	memcpy(&__activeVars->show_logging_cmd__X, &show_logging_cmd_lib, sizeof(show_logging_cmd_lib));
	memcpy(&__activeVars->key_string_cmd__X, &key_string_cmd_lib, sizeof(key_string_cmd_lib));
	memcpy(&__activeVars->access_list_extended_any_mask_cmd__X, &access_list_extended_any_mask_cmd_lib, sizeof(access_list_extended_any_mask_cmd_lib));
	memcpy(&__activeVars->access_list_standard_cmd__X, &access_list_standard_cmd_lib, sizeof(access_list_standard_cmd_lib));
	memcpy(&__activeVars->rmap_description_cmd__X, &rmap_description_cmd_lib, sizeof(rmap_description_cmd_lib));
	memcpy(&__activeVars->access_list_extended_mask_host_cmd__X, &access_list_extended_mask_host_cmd_lib, sizeof(access_list_extended_mask_host_cmd_lib));
	memcpy(&__activeVars->access_list_cmd__X, &access_list_cmd_lib, sizeof(access_list_cmd_lib));
	memcpy(&__activeVars->no_config_log_stdout_cmd__X, &no_config_log_stdout_cmd_lib, sizeof(no_config_log_stdout_cmd_lib));
	memcpy(&__activeVars->show_ip_access_list_name_cmd__X, &show_ip_access_list_name_cmd_lib, sizeof(show_ip_access_list_name_cmd_lib));
	memcpy(&__activeVars->access_list_any_cmd__X, &access_list_any_cmd_lib, sizeof(access_list_any_cmd_lib));
	memcpy(&__activeVars->no_ip_prefix_list_cmd__X, &no_ip_prefix_list_cmd_lib, sizeof(no_ip_prefix_list_cmd_lib));
	memcpy(&__activeVars->no_access_list_extended_host_host_cmd__X, &no_access_list_extended_host_host_cmd_lib, sizeof(no_access_list_extended_host_host_cmd_lib));
	memcpy(&__activeVars->accept_lifetime_month_day_month_day_cmd__X, &accept_lifetime_month_day_month_day_cmd_lib, sizeof(accept_lifetime_month_day_month_day_cmd_lib));
	memcpy(&__activeVars->command_types__X, &command_types__T, sizeof(command_types__T));
	memcpy(&__activeVars->no_access_list_extended_host_mask_cmd__X, &no_access_list_extended_host_mask_cmd_lib, sizeof(no_access_list_extended_host_mask_cmd_lib));
	memcpy(&__activeVars->access_list_standard_nomask_cmd__X, &access_list_standard_nomask_cmd_lib, sizeof(access_list_standard_nomask_cmd_lib));
	memcpy(&__activeVars->ipv6_distribute_list_cmd__X, &ipv6_distribute_list_cmd_lib, sizeof(ipv6_distribute_list_cmd_lib));
	__activeVars->telnet_backward_char__X =  0x08;
	memcpy(&__activeVars->access_list_remark_cmd__X, &access_list_remark_cmd_lib, sizeof(access_list_remark_cmd_lib));
	memcpy(&__activeVars->no_ip_prefix_list_seq_cmd__X, &no_ip_prefix_list_seq_cmd_lib, sizeof(no_ip_prefix_list_seq_cmd_lib));
	memcpy(&__activeVars->ipv6_distribute_list_prefix_cmd__X, &ipv6_distribute_list_prefix_cmd_lib, sizeof(ipv6_distribute_list_prefix_cmd_lib));
	memcpy(&__activeVars->no_rmap_continue_cmd__X, &no_rmap_continue_cmd_lib, sizeof(no_rmap_continue_cmd_lib));
	memcpy(&__activeVars->config_logmsg_cmd__X, &config_logmsg_cmd_lib, sizeof(config_logmsg_cmd_lib));
	__activeVars->vty_cwd__X =  NULL;
	memcpy(&__activeVars->send_lifetime_duration_month_day_cmd__X, &send_lifetime_duration_month_day_cmd_lib, sizeof(send_lifetime_duration_month_day_cmd_lib));
	memcpy(&__activeVars->no_rmap_onmatch_goto_cmd__X, &no_rmap_onmatch_goto_cmd_lib, sizeof(no_rmap_onmatch_goto_cmd_lib));
	memcpy(&__activeVars->show_ip_prefix_list_prefix_longer_cmd__X, &show_ip_prefix_list_prefix_longer_cmd_lib, sizeof(show_ip_prefix_list_prefix_longer_cmd_lib));
	memcpy(&__activeVars->rmap_call_cmd__X, &rmap_call_cmd_lib, sizeof(rmap_call_cmd_lib));
	memcpy(&__activeVars->show_ip_prefix_list_detail_name_cmd__X, &show_ip_prefix_list_detail_name_cmd_lib, sizeof(show_ip_prefix_list_detail_name_cmd_lib));
	memcpy(&__activeVars->config_log_syslog_cmd__X, &config_log_syslog_cmd_lib, sizeof(config_log_syslog_cmd_lib));
	memcpy(&__activeVars->distribute_list_prefix_cmd__X, &distribute_list_prefix_cmd_lib, sizeof(distribute_list_prefix_cmd_lib));
}

extern struct cmd_element no_neighbor_attr_unchanged1_cmd_bgpd;
extern struct cmd_element bgp_network_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_in_prefix_filter_cmd_bgpd;
extern struct cmd_element no_bgp_network_ttl_cmd_bgpd;
extern struct cmd_element show_ip_bgp_scan_cmd_bgpd;
extern struct cmd_element no_match_ip_route_source_val_cmd_bgpd;
extern struct cmd_element show_ip_community_list_arg_cmd_bgpd;
extern struct cmd_element no_neighbor_distribute_list_cmd_bgpd;
extern struct cmd_element bgp_default_local_preference_cmd_bgpd;
extern struct cmd_element no_debug_bgp_as4_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_ipv4_soft_in_cmd_bgpd;
extern struct cmd_element no_neighbor_maximum_prefix_cmd_bgpd;
extern struct cmd_element bgp_network_mask_natural_backdoor_cmd_bgpd;
extern struct cmd_element no_neighbor_attr_unchanged9_cmd_bgpd;
extern struct cmd_element no_set_community_val_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_instance_all_soft_cmd_bgpd;
extern struct cmd_element neighbor_prefix_list_cmd_bgpd;
extern struct cmd_element undebug_bgp_fsm_cmd_bgpd;
extern struct cmd_element no_match_peer_cmd_bgpd;
extern struct cmd_element show_ip_bgp_neighbor_received_routes_cmd_bgpd;
extern struct cmd_element dump_bgp_all_cmd_bgpd;
extern struct cmd_element no_bgp_network_route_map_cmd_bgpd;
extern struct cmd_element no_match_origin_val_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_neighbor_received_routes_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_soft_out_cmd_bgpd;
extern struct cmd_element no_bgp_graceful_restart_cmd_bgpd;
extern struct cmd_element no_router_bgp_cmd_bgpd;
extern struct route_map_rule_cmd route_set_pathlimit_ttl_cmd_bgpd;
extern struct cmd_element clear_bgp_all_cmd_bgpd;
extern struct cmd_element address_family_ipv4_safi_cmd_bgpd;
extern struct cmd_element no_neighbor_default_originate_rmap_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_summary_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_rd_summary_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_in_cmd_bgpd;
extern struct cmd_element show_debugging_bgp_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_external_ipv4_out_cmd_bgpd;
extern struct cmd_element no_neighbor_timers_connect_val_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_soft_cmd_bgpd;
extern struct cmd_element no_neighbor_attr_unchanged3_cmd_bgpd;
extern struct cmd_element no_bgp_network_mask_backdoor_ttl_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_in_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_soft_in_cmd_bgpd;
extern struct cmd_element show_ip_bgp_summary_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_in_cmd_bgpd;
extern struct cmd_element neighbor_allowas_in_arg_cmd_bgpd;
extern struct route_map_rule_cmd route_set_metric_cmd_bgpd;
extern struct cmd_element show_ip_bgp_instance_ipv4_rsclient_summary_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_group_soft_in_cmd_bgpd;
extern struct cmd_element no_neighbor_capability_route_refresh_cmd_bgpd;
extern struct cmd_element neighbor_ebgp_multihop_ttl_cmd_bgpd;
extern struct cmd_element no_debug_bgp_keepalive_cmd_bgpd;
extern struct cmd_element show_ip_bgp_view_prefix_cmd_bgpd;
extern struct cmd_element bgp_deterministic_med_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_group_out_cmd_bgpd;
extern struct cmd_element undebug_bgp_as4_cmd_bgpd;
extern struct cmd_element show_ip_bgp_filter_list_cmd_bgpd;
extern struct cmd_element no_vpnv4_network_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_rd_route_cmd_bgpd;
extern struct cmd_element undebug_bgp_keepalive_cmd_bgpd;
extern struct cmd_element no_neighbor_attr_unchanged5_cmd_bgpd;
extern struct cmd_element aggregate_address_summary_only_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_ipv4_soft_in_cmd_bgpd;
extern struct cmd_element no_set_pathlimit_ttl_val_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_vpnv4_soft_out_cmd_bgpd;
extern struct route_map_rule_cmd route_match_ip_route_source_cmd_bgpd;
extern struct cmd_element no_set_origin_val_cmd_bgpd;
extern struct cmd_element debug_bgp_as4_cmd_bgpd;
extern struct cmd_element bgp_confederation_identifier_cmd_bgpd;
extern struct route_map_rule_cmd route_set_atomic_aggregate_cmd_bgpd;
extern struct route_map_rule_cmd route_set_community_cmd_bgpd;
extern struct cmd_element debug_bgp_update_direct_cmd_bgpd;
extern struct cmd_element show_ip_bgp_flap_filter_list_cmd_bgpd;
extern struct cmd_element bgp_damp_set3_cmd_bgpd;
extern struct cmd_element bgp_network_mask_natural_route_map_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_vpnv4_soft_out_cmd_bgpd;
extern struct cmd_element no_neighbor_remote_as_cmd_bgpd;
extern struct cmd_element set_vpnv4_nexthop_cmd_bgpd;
extern struct cmd_element match_community_exact_cmd_bgpd;
extern struct cmd_element show_ip_bgp_rsclient_summary_cmd_bgpd;
extern struct cmd_element show_bgp_neighbors_peer_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_all_neighbors_cmd_bgpd;
extern struct cmd_element neighbor_send_community_cmd_bgpd;
extern struct cmd_element no_set_pathlimit_ttl_cmd_bgpd;
extern struct cmd_element neighbor_route_reflector_client_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_soft_cmd_bgpd;
extern struct cmd_element dump_bgp_updates_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_in_prefix_filter_cmd_bgpd;
extern struct cmd_element show_ip_bgp_community_list_exact_cmd_bgpd;
extern struct route_map_rule_cmd route_set_vpnv4_nexthop_cmd_bgpd;
extern struct cmd_element ip_extcommunity_list_standard_cmd_bgpd;
extern struct cmd_element bgp_network_mask_ttl_cmd_bgpd;
extern struct cmd_element no_neighbor_filter_list_cmd_bgpd;
extern struct cmd_element no_bgp_config_type_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_all_soft_out_cmd_bgpd;
extern struct cmd_element no_bgp_bestpath_med2_cmd_bgpd;
extern struct route_map_rule_cmd route_set_ip_nexthop_cmd_bgpd;
extern struct cmd_element no_bgp_multiple_instance_cmd_bgpd;
extern struct cmd_element no_debug_bgp_events_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_ipv4_soft_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_group_cmd_bgpd;
extern struct cmd_element no_neighbor_port_val_cmd_bgpd;
extern struct cmd_element show_ip_bgp_community3_exact_cmd_bgpd;
extern struct route_map_rule_cmd route_match_pathlimit_as_cmd_bgpd;
extern struct cmd_element no_match_ip_route_source_prefix_list_cmd_bgpd;
extern struct cmd_element bgp_distance_source_access_list_cmd_bgpd;
extern struct cmd_element show_ip_bgp_community3_cmd_bgpd;
extern struct cmd_element ip_community_list_name_standard2_cmd_bgpd;
extern struct cmd_element ip_extcommunity_list_name_expanded_cmd_bgpd;
extern struct cmd_element clear_bgp_as_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_neighbor_prefix_counts_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_group_cmd_bgpd;
extern struct cmd_element no_neighbor_nexthop_local_unchanged_cmd_bgpd;
extern struct cmd_element show_ip_bgp_rsclient_cmd_bgpd;
extern struct cmd_element show_bgp_statistics_cmd_bgpd;
extern struct cmd_element show_ip_bgp_community_cmd_bgpd;
extern struct cmd_element show_bgp_statistics_vpnv4_cmd_bgpd;
extern struct cmd_element neighbor_maximum_prefix_threshold_cmd_bgpd;
extern struct cmd_element show_bgp_statistics_view_cmd_bgpd;
extern struct route_map_rule_cmd route_set_ecommunity_rt_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_neighbor_received_prefix_filter_cmd_bgpd;
extern struct cmd_element neighbor_maximum_prefix_cmd_bgpd;
extern struct cmd_element no_set_ecommunity_rt_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_instance_all_ipv4_soft_in_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_in_prefix_filter_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_all_cmd_bgpd;
extern struct cmd_element router_bgp_view_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_community_all_cmd_bgpd;
extern struct cmd_element clear_bgp_as_soft_cmd_bgpd;
extern struct cmd_element no_ip_community_list_name_expanded_all_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_ipv4_out_cmd_bgpd;
extern struct cmd_element no_neighbor_route_server_client_cmd_bgpd;
extern struct cmd_element no_bgp_distance_source_access_list_cmd_bgpd;
extern struct cmd_element no_bgp_confederation_identifier_cmd_bgpd;
extern struct cmd_element neighbor_update_source_cmd_bgpd;
extern struct cmd_element no_set_ecommunity_soo_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_neighbors_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_ipv4_soft_out_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_vpnv4_soft_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_out_cmd_bgpd;
extern struct cmd_element no_neighbor_ebgp_multihop_ttl_cmd_bgpd;
extern struct cmd_element bgp_redistribute_ipv4_cmd_bgpd;
extern struct cmd_element neighbor_maximum_prefix_threshold_warning_cmd_bgpd;
extern struct cmd_element no_neighbor_interface_cmd_bgpd;
extern struct cmd_element neighbor_peer_group_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_ipv4_in_prefix_filter_cmd_bgpd;
extern struct cmd_element show_ip_bgp_flap_cidr_only_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_all_summary_cmd_bgpd;
extern struct cmd_element clear_bgp_external_cmd_bgpd;
extern struct cmd_element address_family_vpnv4_cmd_bgpd;
extern struct cmd_element no_bgp_router_id_cmd_bgpd;
extern struct cmd_element set_metric_addsub_cmd_bgpd;
extern struct cmd_element clear_bgp_external_soft_cmd_bgpd;
extern struct cmd_element address_family_vpnv4_unicast_cmd_bgpd;
extern struct cmd_element show_ip_as_path_access_list_all_cmd_bgpd;
extern struct cmd_element no_neighbor_attr_unchanged_cmd_bgpd;
extern struct cmd_element no_neighbor_shutdown_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_external_soft_in_cmd_bgpd;
extern struct cmd_element set_community_none_cmd_bgpd;
extern struct cmd_element match_ip_route_source_prefix_list_cmd_bgpd;
extern struct cmd_element neighbor_attr_unchanged6_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_as_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_rd_neighbors_peer_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_group_soft_out_cmd_bgpd;
extern struct cmd_element no_neighbor_ebgp_multihop_cmd_bgpd;
extern struct cmd_element no_aggregate_address_as_set_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_instance_all_ipv4_soft_out_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_all_out_cmd_bgpd;
extern struct cmd_element bgp_config_type_cmd_bgpd;
extern struct cmd_element neighbor_attr_unchanged10_cmd_bgpd;
extern struct cmd_element no_bgp_network_backdoor_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_soft_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_external_soft_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_ipv4_in_cmd_bgpd;
extern struct cmd_element aggregate_address_mask_summary_only_cmd_bgpd;
extern struct cmd_element show_ip_bgp_community_all_cmd_bgpd;
extern struct cmd_element no_neighbor_attr_unchanged8_cmd_bgpd;
extern struct cmd_element no_aggregate_address_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_soft_out_cmd_bgpd;
extern struct cmd_element show_ip_bgp_view_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_rd_neighbors_cmd_bgpd;
extern struct cmd_element no_neighbor_allowas_in_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_ipv4_in_prefix_filter_cmd_bgpd;
extern struct cmd_element show_ip_bgp_neighbor_routes_cmd_bgpd;
extern struct cmd_element aggregate_address_mask_as_set_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_vpnv4_soft_in_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_community4_exact_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_prefix_cmd_bgpd;
extern struct cmd_element set_community_delete_cmd_bgpd;
extern struct cmd_element neighbor_override_capability_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_external_soft_out_cmd_bgpd;
extern struct cmd_element no_ip_as_path_cmd_bgpd;
extern struct cmd_element neighbor_default_originate_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_prefix_list_cmd_bgpd;
extern struct route_map_rule_cmd route_match_metric_cmd_bgpd;
extern struct cmd_element no_neighbor_capability_orf_prefix_cmd_bgpd;
extern struct cmd_element neighbor_maximum_prefix_threshold_restart_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_community2_exact_cmd_bgpd;
extern struct cmd_element clear_bgp_all_out_cmd_bgpd;
extern struct cmd_element bgp_fast_external_failover_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_group_ipv4_out_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_out_cmd_bgpd;
extern struct cmd_element no_set_metric_val_cmd_bgpd;
extern struct cmd_element neighbor_activate_cmd_bgpd;
extern struct cmd_element no_bgp_network_mask_route_map_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_all_route_cmd_bgpd;
extern struct cmd_element clear_bgp_instance_all_soft_in_cmd_bgpd;
extern struct cmd_element neighbor_description_cmd_bgpd;
extern struct cmd_element no_neighbor_enforce_multihop_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_external_ipv4_soft_in_cmd_bgpd;
extern struct cmd_element aggregate_address_mask_as_set_summary_cmd_bgpd;
extern struct cmd_element show_bgp_ipv6_route_map_cmd_bgpd;
extern struct cmd_element no_set_local_pref_cmd_bgpd;
extern struct cmd_element no_bgp_client_to_client_reflection_cmd_bgpd;
extern struct cmd_element no_neighbor_port_cmd_bgpd;
extern struct cmd_element no_neighbor_route_reflector_client_cmd_bgpd;
extern struct cmd_element no_set_community_delete_cmd_bgpd;
extern struct cmd_element neighbor_remote_as_cmd_bgpd;
extern struct cmd_element no_bgp_fast_external_failover_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_group_out_cmd_bgpd;
extern struct cmd_element no_bgp_network_mask_natural_backdoor_ttl_cmd_bgpd;
extern struct cmd_element no_match_pathlimit_as_val_cmd_bgpd;
extern struct cmd_element no_match_ip_address_cmd_bgpd;
extern struct cmd_element neighbor_route_server_client_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_ipv4_soft_in_cmd_bgpd;
extern struct cmd_element neighbor_filter_list_cmd_bgpd;
extern struct cmd_element show_ip_bgp_attr_info_cmd_bgpd;
extern struct cmd_element neighbor_strict_capability_cmd_bgpd;
extern struct cmd_element show_bgp_instance_ipv6_neighbors_peer_cmd_bgpd;
extern struct route_map_rule_cmd route_set_local_pref_cmd_bgpd;
extern struct cmd_element show_ip_bgp_prefix_cmd_bgpd;
extern struct cmd_element show_ip_bgp_neighbor_advertised_route_cmd_bgpd;
extern struct cmd_element clear_bgp_as_in_prefix_filter_cmd_bgpd;
extern struct cmd_element show_bgp_ipv6_neighbors_cmd_bgpd;
extern struct cmd_element no_set_vpnv4_nexthop_cmd_bgpd;
extern struct cmd_element no_match_community_exact_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_instance_all_rsclient_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_dampening_prefix_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_cmd_bgpd;
extern struct cmd_element ip_community_list_standard2_cmd_bgpd;
extern struct cmd_element no_ip_extcommunity_list_name_standard_all_cmd_bgpd;
extern struct cmd_element show_ip_bgp_instance_ipv4_summary_cmd_bgpd;
extern struct cmd_element no_bgp_network_mask_natural_route_map_cmd_bgpd;
extern struct cmd_element show_ip_bgp_prefix_list_cmd_bgpd;
extern struct cmd_element no_bgp_redistribute_ipv4_metric_cmd_bgpd;
extern struct route_map_rule_cmd route_match_ip_next_hop_prefix_list_cmd_bgpd;
extern struct cmd_element no_neighbor_password_cmd_bgpd;
extern struct cmd_element debug_bgp_fsm_cmd_bgpd;
extern struct cmd_element no_aggregate_address_mask_as_set_summary_cmd_bgpd;
extern struct cmd_element show_ip_bgp_community2_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_rd_cmd_bgpd;
extern struct cmd_element show_ip_bgp_community_exact_cmd_bgpd;
extern struct cmd_element show_bgp_instance_neighbors_cmd_bgpd;
extern struct cmd_element show_bgp_instance_neighbors_peer_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_soft_cmd_bgpd;
extern struct cmd_element no_neighbor_advertise_interval_cmd_bgpd;
extern struct cmd_element neighbor_soft_reconfiguration_cmd_bgpd;
extern struct cmd_element no_match_origin_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_soft_out_cmd_bgpd;
extern struct cmd_element no_bgp_scan_time_cmd_bgpd;
extern struct cmd_element aggregate_address_cmd_bgpd;
extern struct cmd_element no_neighbor_description_cmd_bgpd;
extern struct cmd_element undebug_bgp_normal_cmd_bgpd;
extern struct cmd_element aggregate_address_mask_cmd_bgpd;
extern struct cmd_element ip_community_list_expanded_cmd_bgpd;
extern struct cmd_element clear_bgp_external_soft_out_cmd_bgpd;
extern struct cmd_element no_match_pathlimit_as_cmd_bgpd;
extern struct cmd_element no_bgp_bestpath_aspath_confed_cmd_bgpd;
extern struct cmd_element no_bgp_network_cmd_bgpd;
extern struct cmd_element show_ip_bgp_flap_route_map_cmd_bgpd;
extern struct cmd_element no_neighbor_maximum_prefix_warning_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_external_out_cmd_bgpd;
extern struct cmd_element bgp_multiple_instance_cmd_bgpd;
extern struct cmd_element no_bgp_log_neighbor_changes_cmd_bgpd;
extern struct cmd_element match_ip_next_hop_prefix_list_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_in_cmd_bgpd;
extern struct cmd_element neighbor_attr_unchanged4_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_in_cmd_bgpd;
extern struct cmd_element neighbor_default_originate_rmap_cmd_bgpd;
extern struct cmd_element match_ip_address_prefix_list_cmd_bgpd;
extern struct cmd_element no_set_aspath_exclude_val_cmd_bgpd;
extern struct cmd_element no_set_ip_nexthop_peer_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_all_cmd_bgpd;
extern struct cmd_element show_ip_bgp_prefix_longer_cmd_bgpd;
extern struct cmd_element clear_bgp_instance_all_soft_out_cmd_bgpd;
extern struct cmd_element exit_address_family_cmd_bgpd;
extern struct cmd_element no_neighbor_attr_unchanged2_cmd_bgpd;
extern struct cmd_element no_match_metric_cmd_bgpd;
extern struct cmd_element bgp_bestpath_med3_cmd_bgpd;
extern struct cmd_element set_ip_nexthop_cmd_bgpd;
extern struct cmd_element bgp_client_to_client_reflection_cmd_bgpd;
extern struct cmd_element bgp_network_ttl_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_dampening_address_mask_cmd_bgpd;
extern struct cmd_element dump_bgp_updates_interval_cmd_bgpd;
extern struct cmd_element no_ip_community_list_standard_all_cmd_bgpd;
extern struct cmd_element no_bgp_redistribute_ipv4_rmap_metric_cmd_bgpd;
extern struct cmd_element no_ip_extcommunity_list_expanded_all_cmd_bgpd;
extern struct cmd_element set_atomic_aggregate_cmd_bgpd;
extern struct cmd_element no_match_ip_next_hop_val_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_all_neighbor_advertised_routes_cmd_bgpd;
extern struct cmd_element no_neighbor_soft_reconfiguration_cmd_bgpd;
extern struct cmd_element no_bgp_distance_cmd_bgpd;
extern struct cmd_element no_bgp_default_local_preference_cmd_bgpd;
extern struct cmd_element no_bgp_bestpath_compare_router_id_cmd_bgpd;
extern struct cmd_element match_community_cmd_bgpd;
extern struct cmd_element no_neighbor_maximum_prefix_restart_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_rd_tags_cmd_bgpd;
extern struct cmd_element show_bgp_neighbors_cmd_bgpd;
extern struct cmd_element no_set_originator_id_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_all_prefix_cmd_bgpd;
extern struct cmd_element no_neighbor_maximum_prefix_threshold_warning_cmd_bgpd;
extern struct cmd_element show_ip_bgp_rsclient_prefix_cmd_bgpd;
extern struct cmd_element no_bgp_network_mask_natural_backdoor_cmd_bgpd;
extern struct route_map_rule_cmd route_match_aspath_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_cmd_bgpd;
extern struct route_map_rule_cmd route_set_originator_id_cmd_bgpd;
extern struct cmd_element no_bgp_distance2_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_instance_all_in_prefix_filter_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_ipv4_soft_out_cmd_bgpd;
extern struct cmd_element no_neighbor_maximum_prefix_val_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_group_in_prefix_filter_cmd_bgpd;
extern struct cmd_element aggregate_address_as_set_summary_cmd_bgpd;
extern struct cmd_element no_bgp_network_mask_backdoor_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_ipv4_soft_cmd_bgpd;
extern struct cmd_element no_router_bgp_view_cmd_bgpd;
extern struct cmd_element no_neighbor_send_community_type_cmd_bgpd;
extern struct cmd_element no_ip_extcommunity_list_name_expanded_cmd_bgpd;
extern struct cmd_element no_ip_community_list_name_expanded_cmd_bgpd;
extern struct cmd_element no_bgp_bestpath_aspath_ignore_cmd_bgpd;
extern struct cmd_element no_bgp_graceful_restart_stalepath_time_val_cmd_bgpd;
extern struct cmd_element undebug_bgp_update_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_group_ipv4_soft_in_cmd_bgpd;
extern struct cmd_element no_set_vpnv4_nexthop_val_cmd_bgpd;
extern struct cmd_element show_ip_community_list_cmd_bgpd;
extern struct cmd_element bgp_default_ipv4_unicast_cmd_bgpd;
extern struct cmd_element set_weight_cmd_bgpd;
extern struct cmd_element no_bgp_redistribute_ipv4_rmap_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_rd_prefix_cmd_bgpd;
extern struct cmd_element neighbor_version_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_external_in_prefix_filter_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_vpnv4_soft_out_cmd_bgpd;
extern struct cmd_element no_ip_community_list_name_standard_all_cmd_bgpd;
extern struct cmd_element no_neighbor_attr_unchanged6_cmd_bgpd;
extern struct cmd_element neighbor_transparent_nexthop_cmd_bgpd;
extern struct cmd_element no_match_ip_next_hop_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_external_in_cmd_bgpd;
extern struct cmd_element undebug_bgp_filter_cmd_bgpd;
extern struct route_map_rule_cmd route_set_weight_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_instance_peer_rsclient_cmd_bgpd;
extern struct cmd_element neighbor_unsuppress_map_cmd_bgpd;
extern struct cmd_element no_dump_bgp_updates_cmd_bgpd;
extern struct cmd_element no_neighbor_local_as_val2_cmd_bgpd;
extern struct cmd_element no_match_ip_next_hop_prefix_list_cmd_bgpd;
extern struct cmd_element no_dump_bgp_all_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_neighbor_advertised_route_cmd_bgpd;
extern struct cmd_element no_set_local_pref_val_cmd_bgpd;
extern struct cmd_element no_bgp_network_backdoor_ttl_cmd_bgpd;
extern struct cmd_element neighbor_advertise_interval_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_in_prefix_filter_cmd_bgpd;
extern struct cmd_element neighbor_attr_unchanged1_cmd_bgpd;
extern struct cmd_element show_ip_bgp_view_rsclient_cmd_bgpd;
extern struct cmd_element neighbor_dont_capability_negotiate_cmd_bgpd;
extern struct cmd_element vpnv4_network_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_group_soft_cmd_bgpd;
extern struct cmd_element no_bgp_default_ipv4_unicast_cmd_bgpd;
extern struct cmd_element dump_bgp_all_interval_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_group_in_cmd_bgpd;
extern struct cmd_element match_peer_local_cmd_bgpd;
extern struct cmd_element no_ip_extcommunity_list_expanded_cmd_bgpd;
extern struct cmd_element bgp_log_neighbor_changes_cmd_bgpd;
extern struct cmd_element bgp_enforce_first_as_cmd_bgpd;
extern struct cmd_element no_neighbor_activate_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_group_ipv4_in_prefix_filter_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_as_in_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_route_map_cmd_bgpd;
extern struct cmd_element no_set_community_cmd_bgpd;
extern struct cmd_element no_neighbor_passive_cmd_bgpd;
extern struct cmd_element no_neighbor_maximum_prefix_threshold_cmd_bgpd;
extern struct cmd_element no_neighbor_peer_group_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_vpnv4_out_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_soft_out_cmd_bgpd;
extern struct cmd_element address_family_ipv6_cmd_bgpd;
extern struct cmd_element no_bgp_redistribute_ipv4_cmd_bgpd;
extern struct cmd_element no_bgp_timers_arg_cmd_bgpd;
extern struct cmd_element no_match_peer_local_cmd_bgpd;
extern struct cmd_element no_set_ip_nexthop_val_cmd_bgpd;
extern struct cmd_element no_bgp_network_mask_natural_ttl_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_as_soft_in_cmd_bgpd;
extern struct cmd_element no_bgp_network_import_check_cmd_bgpd;
extern struct cmd_element no_ip_community_list_standard_cmd_bgpd;
extern struct cmd_element address_family_ipv6_safi_cmd_bgpd;
extern struct cmd_element no_match_ip_route_source_prefix_list_val_cmd_bgpd;
extern struct cmd_element bgp_network_mask_cmd_bgpd;
extern struct cmd_element show_ip_bgp_community4_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_rsclient_cmd_bgpd;
extern struct cmd_element bgp_network_backdoor_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_instance_all_cmd_bgpd;
extern struct cmd_element no_match_ecommunity_val_cmd_bgpd;
extern struct cmd_element show_ip_bgp_flap_prefix_longer_cmd_bgpd;
extern struct cmd_element no_set_weight_cmd_bgpd;
extern struct cmd_element show_bgp_views_cmd_bgpd;
extern struct cmd_element neighbor_distribute_list_cmd_bgpd;
extern struct cmd_element ip_as_path_cmd_bgpd;
extern struct cmd_element no_match_community_cmd_bgpd;
extern struct cmd_element set_ip_nexthop_peer_cmd_bgpd;
extern struct cmd_element neighbor_timers_cmd_bgpd;
extern struct cmd_element no_set_aggregator_as_cmd_bgpd;
extern struct cmd_element no_bgp_bestpath_med_cmd_bgpd;
extern struct route_map_rule_cmd route_match_ip_next_hop_cmd_bgpd;
extern struct cmd_element bgp_damp_set2_cmd_bgpd;
extern struct cmd_element show_ip_bgp_flap_statistics_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_vpnv4_soft_cmd_bgpd;
extern struct route_map_rule_cmd route_set_aggregator_as_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_all_in_prefix_filter_cmd_bgpd;
extern struct cmd_element debug_bgp_normal_cmd_bgpd;
extern struct cmd_element no_bgp_network_mask_ttl_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_external_out_cmd_bgpd;
extern struct cmd_element debug_bgp_zebra_cmd_bgpd;
extern struct cmd_element no_neighbor_weight_val_cmd_bgpd;
extern struct route_map_rule_cmd route_set_aspath_exclude_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_paths_cmd_bgpd;
extern struct cmd_element no_bgp_distance_source_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_out_cmd_bgpd;
extern struct cmd_element show_bgp_memory_cmd_bgpd;
extern struct cmd_element neighbor_set_peer_group_cmd_bgpd;
extern struct cmd_element debug_bgp_update_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_ipv4_out_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_soft_out_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_regexp_cmd_bgpd;
extern struct cmd_element match_ecommunity_cmd_bgpd;
extern struct cmd_element no_ip_community_list_name_standard_cmd_bgpd;
extern struct cmd_element no_match_ip_address_prefix_list_val_cmd_bgpd;
extern struct cmd_element show_ip_bgp_instance_summary_cmd_bgpd;
extern struct cmd_element clear_bgp_as_soft_out_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_group_soft_cmd_bgpd;
extern struct cmd_element set_metric_cmd_bgpd;
extern struct cmd_element bgp_timers_cmd_bgpd;
extern struct cmd_element neighbor_interface_cmd_bgpd;
extern struct cmd_element neighbor_send_community_type_cmd_bgpd;
extern struct cmd_element show_ip_bgp_neighbor_flap_cmd_bgpd;
extern struct cmd_element no_ip_as_path_all_cmd_bgpd;
extern struct cmd_element no_neighbor_send_community_cmd_bgpd;
extern struct cmd_element no_neighbor_strict_capability_cmd_bgpd;
extern struct cmd_element no_neighbor_update_source_cmd_bgpd;
extern struct cmd_element match_origin_cmd_bgpd;
extern struct cmd_element no_neighbor_timers_connect_cmd_bgpd;
extern struct cmd_element set_aspath_prepend_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_external_ipv4_in_cmd_bgpd;
extern struct cmd_element show_ip_bgp_regexp_cmd_bgpd;
extern struct cmd_element ip_community_list_name_standard_cmd_bgpd;
extern struct cmd_element clear_bgp_as_out_cmd_bgpd;
extern struct cmd_element no_neighbor_weight_cmd_bgpd;
extern struct cmd_element bgp_redistribute_ipv4_rmap_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_group_ipv4_in_cmd_bgpd;
extern struct cmd_element dump_bgp_routes_interval_cmd_bgpd;
extern struct cmd_element show_ip_bgp_dampened_paths_cmd_bgpd;
extern struct cmd_element no_aggregate_address_as_set_summary_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_group_in_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_external_in_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_neighbor_routes_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_cmd_bgpd;
extern struct cmd_element no_neighbor_nexthop_self_cmd_bgpd;
extern struct cmd_element debug_bgp_as4_segment_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_group_out_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_all_tags_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_vpnv4_out_cmd_bgpd;
extern struct cmd_element no_match_ip_address_val_cmd_bgpd;
extern struct cmd_element no_neighbor_attr_unchanged10_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_external_soft_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_as_in_prefix_filter_cmd_bgpd;
extern struct cmd_element no_debug_bgp_fsm_cmd_bgpd;
extern struct cmd_element show_ip_bgp_flap_prefix_cmd_bgpd;
extern struct cmd_element no_debug_bgp_update_cmd_bgpd;
extern struct cmd_element bgp_network_mask_natural_ttl_cmd_bgpd;
extern struct cmd_element match_ip_route_source_cmd_bgpd;
extern struct cmd_element clear_bgp_as_in_cmd_bgpd;
extern struct cmd_element show_ip_bgp_view_route_cmd_bgpd;
extern struct cmd_element no_bgp_confederation_identifier_arg_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_cmd_bgpd;
extern struct cmd_element no_set_ecommunity_rt_val_cmd_bgpd;
extern struct cmd_element neighbor_attr_unchanged_cmd_bgpd;
extern struct cmd_element show_ip_bgp_neighbors_cmd_bgpd;
extern struct route_map_rule_cmd route_match_peer_cmd_bgpd;
extern struct cmd_element bgp_network_mask_natural_cmd_bgpd;
extern struct cmd_element debug_bgp_events_cmd_bgpd;
extern struct cmd_element set_pathlimit_ttl_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_in_prefix_filter_cmd_bgpd;
extern struct cmd_element clear_bgp_all_soft_in_cmd_bgpd;
extern struct cmd_element bgp_network_backdoor_ttl_cmd_bgpd;
extern struct cmd_element show_ip_bgp_paths_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_ipv4_in_cmd_bgpd;
extern struct cmd_element no_bgp_scan_time_val_cmd_bgpd;
extern struct cmd_element no_debug_bgp_all_cmd_bgpd;
extern struct cmd_element show_ip_bgp_flap_address_cmd_bgpd;
extern struct cmd_element show_ip_extcommunity_list_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_external_soft_in_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_filter_list_cmd_bgpd;
extern struct cmd_element no_bgp_cluster_id_arg_cmd_bgpd;
extern struct cmd_element bgp_graceful_restart_stalepath_time_cmd_bgpd;
extern struct cmd_element set_aspath_exclude_cmd_bgpd;
extern struct route_map_rule_cmd route_match_ip_address_prefix_list_cmd_bgpd;
extern struct cmd_element neighbor_passive_cmd_bgpd;
extern struct cmd_element neighbor_timers_connect_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_external_ipv4_soft_out_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_group_soft_out_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_group_soft_cmd_bgpd;
extern struct cmd_element undebug_bgp_zebra_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_neighbors_peer_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_ipv4_soft_cmd_bgpd;
extern struct cmd_element router_bgp_cmd_bgpd;
extern struct cmd_element no_debug_bgp_as4_segment_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_out_cmd_bgpd;
extern struct cmd_element set_community_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_external_cmd_bgpd;
extern struct cmd_element no_bgp_network_mask_natural_cmd_bgpd;
extern struct cmd_element no_set_metric_cmd_bgpd;
extern struct cmd_element no_match_ip_route_source_cmd_bgpd;
extern struct cmd_element bgp_confederation_peers_cmd_bgpd;
extern struct cmd_element show_ip_bgp_neighbors_peer_cmd_bgpd;
extern struct cmd_element clear_bgp_external_in_prefix_filter_cmd_bgpd;
extern struct cmd_element undebug_bgp_events_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_instance_all_ipv4_in_prefix_filter_cmd_bgpd;
extern struct cmd_element bgp_distance_cmd_bgpd;
extern struct cmd_element clear_bgp_external_in_cmd_bgpd;
extern struct cmd_element neighbor_shutdown_cmd_bgpd;
extern struct cmd_element clear_bgp_external_out_cmd_bgpd;
extern struct cmd_element show_ip_bgp_cmd_bgpd;
extern struct cmd_element no_neighbor_remove_private_as_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_rd_neighbor_routes_cmd_bgpd;
extern struct cmd_element neighbor_local_as_no_prepend_cmd_bgpd;
extern struct cmd_element bgp_router_id_cmd_bgpd;
extern struct cmd_element aggregate_address_summary_as_set_cmd_bgpd;
extern struct cmd_element neighbor_port_cmd_bgpd;
extern struct cmd_element no_debug_bgp_normal_cmd_bgpd;
extern struct cmd_element no_neighbor_override_capability_cmd_bgpd;
extern struct cmd_element show_ip_bgp_community_list_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_rsclient_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_all_soft_cmd_bgpd;
extern struct cmd_element debug_bgp_filter_cmd_bgpd;
extern struct cmd_element neighbor_enforce_multihop_cmd_bgpd;
extern struct cmd_element no_neighbor_dont_capability_negotiate_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_community_exact_cmd_bgpd;
extern struct cmd_element no_neighbor_maximum_prefix_threshold_restart_cmd_bgpd;
extern struct cmd_element neighbor_maximum_prefix_warning_cmd_bgpd;
extern struct cmd_element no_bgp_router_id_val_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_soft_in_cmd_bgpd;
extern struct cmd_element show_ip_bgp_flap_prefix_list_cmd_bgpd;
extern struct cmd_element no_match_ip_next_hop_prefix_list_val_cmd_bgpd;
extern struct cmd_element undebug_bgp_all_cmd_bgpd;
extern struct cmd_element no_set_atomic_aggregate_cmd_bgpd;
extern struct cmd_element no_set_aspath_exclude_cmd_bgpd;
extern struct cmd_element show_bgp_ipv6_neighbor_prefix_counts_cmd_bgpd;
extern struct cmd_element no_neighbor_default_originate_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_dampening_address_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_as_soft_cmd_bgpd;
extern struct cmd_element no_set_ip_nexthop_cmd_bgpd;
extern struct cmd_element ip_extcommunity_list_standard2_cmd_bgpd;
extern struct cmd_element neighbor_maximum_prefix_restart_cmd_bgpd;
extern struct route_map_rule_cmd route_set_ecommunity_soo_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_instance_all_ipv4_soft_cmd_bgpd;
extern struct cmd_element show_ip_bgp_rsclient_route_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_external_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_vpnv4_soft_cmd_bgpd;
extern struct cmd_element show_ip_bgp_route_map_cmd_bgpd;
extern struct cmd_element no_set_community_delete_val_cmd_bgpd;
extern struct cmd_element neighbor_remove_private_as_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_neighbor_prefix_counts_cmd_bgpd;
extern struct cmd_element neighbor_nexthop_local_unchanged_cmd_bgpd;
extern struct cmd_element no_ip_community_list_expanded_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_dampening_cmd_bgpd;
extern struct cmd_element no_ip_extcommunity_list_standard_cmd_bgpd;
extern struct cmd_element no_match_community_val_cmd_bgpd;
extern struct cmd_element clear_bgp_external_soft_in_cmd_bgpd;
extern struct cmd_element bgp_bestpath_compare_router_id_cmd_bgpd;
extern struct cmd_element match_metric_cmd_bgpd;
extern struct cmd_element no_neighbor_cmd_bgpd;
extern struct cmd_element show_bgp_statistics_view_vpnv4_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_ipv4_in_cmd_bgpd;
extern struct cmd_element clear_bgp_all_in_prefix_filter_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_instance_all_soft_in_cmd_bgpd;
extern struct cmd_element bgp_network_mask_backdoor_cmd_bgpd;
extern struct cmd_element no_match_ecommunity_cmd_bgpd;
extern struct cmd_element no_bgp_bestpath_med3_cmd_bgpd;
extern struct cmd_element debug_bgp_keepalive_cmd_bgpd;
extern struct route_map_rule_cmd route_set_aspath_prepend_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_as_out_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_route_cmd_bgpd;
extern struct cmd_element dump_bgp_routes_cmd_bgpd;
extern struct route_map_rule_cmd route_match_community_cmd_bgpd;
extern struct cmd_element no_match_aspath_val_cmd_bgpd;
extern struct cmd_element no_set_origin_cmd_bgpd;
extern struct cmd_element neighbor_attr_unchanged8_cmd_bgpd;
extern struct cmd_element no_ip_extcommunity_list_name_expanded_all_cmd_bgpd;
extern struct cmd_element no_synchronization_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_community_list_cmd_bgpd;
extern struct cmd_element neighbor_capability_dynamic_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_group_soft_in_cmd_bgpd;
extern struct cmd_element no_neighbor_description_val_cmd_bgpd;
extern struct cmd_element clear_bgp_instance_all_soft_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_group_cmd_bgpd;
extern struct cmd_element no_aggregate_address_mask_summary_as_set_cmd_bgpd;
extern struct cmd_element match_ip_address_cmd_bgpd;
extern struct cmd_element no_set_originator_id_val_cmd_bgpd;
extern struct cmd_element no_aggregate_address_summary_as_set_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_cidr_only_cmd_bgpd;
extern struct cmd_element set_local_pref_cmd_bgpd;
extern struct cmd_element set_aggregator_as_cmd_bgpd;
extern struct cmd_element bgp_bestpath_med_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_soft_in_cmd_bgpd;
extern struct route_map_rule_cmd route_match_ip_route_source_prefix_list_cmd_bgpd;
extern struct cmd_element bgp_bestpath_med2_cmd_bgpd;
extern struct cmd_element no_neighbor_local_as_cmd_bgpd;
extern struct cmd_element neighbor_attr_unchanged3_cmd_bgpd;
extern struct cmd_element no_neighbor_attr_unchanged7_cmd_bgpd;
extern struct cmd_element neighbor_attr_unchanged7_cmd_bgpd;
extern struct cmd_element no_bgp_enforce_first_as_cmd_bgpd;
extern struct cmd_element no_aggregate_address_mask_summary_only_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_vpnv4_in_cmd_bgpd;
extern struct cmd_element no_neighbor_unsuppress_map_cmd_bgpd;
extern struct cmd_element undebug_bgp_as4_segment_cmd_bgpd;
extern struct cmd_element no_neighbor_route_map_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_group_in_prefix_filter_cmd_bgpd;
extern struct cmd_element no_debug_bgp_zebra_cmd_bgpd;
extern struct route_map_rule_cmd route_set_community_delete_cmd_bgpd;
extern struct cmd_element show_bgp_ipv6_neighbors_peer_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_group_ipv4_soft_cmd_bgpd;
extern struct cmd_element neighbor_allowas_in_cmd_bgpd;
extern struct cmd_element no_auto_summary_cmd_bgpd;
extern struct cmd_element bgp_network_mask_natural_backdoor_ttl_cmd_bgpd;
extern struct cmd_element no_neighbor_capability_dynamic_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_soft_cmd_bgpd;
extern struct cmd_element show_ip_extcommunity_list_arg_cmd_bgpd;
extern struct cmd_element bgp_bestpath_aspath_ignore_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_all_neighbors_peer_cmd_bgpd;
extern struct cmd_element set_originator_id_cmd_bgpd;
extern struct cmd_element ip_community_list_name_expanded_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_vpnv4_out_cmd_bgpd;
extern struct route_map_rule_cmd route_match_ip_address_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_ipv4_out_cmd_bgpd;
extern struct cmd_element show_ip_bgp_view_rsclient_route_cmd_bgpd;
extern struct cmd_element no_match_peer_val_cmd_bgpd;
extern struct cmd_element no_debug_bgp_filter_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_community_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_all_neighbor_routes_cmd_bgpd;
extern struct route_map_rule_cmd route_set_origin_cmd_bgpd;
extern struct cmd_element no_neighbor_disable_connected_check_cmd_bgpd;
extern struct cmd_element show_ip_bgp_community2_exact_cmd_bgpd;
extern struct cmd_element no_set_community_none_cmd_bgpd;
extern struct cmd_element show_ip_bgp_flap_regexp_cmd_bgpd;
extern struct cmd_element neighbor_password_cmd_bgpd;
extern struct cmd_element bgp_redistribute_ipv4_rmap_metric_cmd_bgpd;
extern struct cmd_element show_ip_bgp_community_info_cmd_bgpd;
extern struct cmd_element no_set_aggregator_as_val_cmd_bgpd;
extern struct cmd_element bgp_bestpath_aspath_confed_cmd_bgpd;
extern struct cmd_element neighbor_attr_unchanged9_cmd_bgpd;
extern struct cmd_element no_set_ecommunity_soo_val_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_group_ipv4_soft_out_cmd_bgpd;
extern struct cmd_element show_ip_bgp_instance_neighbors_peer_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_out_cmd_bgpd;
extern struct cmd_element no_bgp_always_compare_med_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_as_soft_out_cmd_bgpd;
extern struct cmd_element set_origin_cmd_bgpd;
extern struct cmd_element neighbor_disable_connected_check_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_external_in_prefix_filter_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_vpnv4_soft_in_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_all_soft_in_cmd_bgpd;
extern struct cmd_element show_ip_as_path_access_list_cmd_bgpd;
extern struct route_map_rule_cmd route_match_origin_cmd_bgpd;
extern struct cmd_element set_ecommunity_rt_cmd_bgpd;
extern struct cmd_element neighbor_local_as_cmd_bgpd;
extern struct cmd_element no_ip_extcommunity_list_standard_all_cmd_bgpd;
extern struct cmd_element show_ip_bgp_cidr_only_cmd_bgpd;
extern struct cmd_element neighbor_route_map_cmd_bgpd;
extern struct cmd_element neighbor_transparent_as_cmd_bgpd;
extern struct cmd_element ip_extcommunity_list_expanded_cmd_bgpd;
extern struct cmd_element show_ip_bgp_route_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_external_ipv4_in_prefix_filter_cmd_bgpd;
extern struct cmd_element show_ip_bgp_vpnv4_rd_neighbor_advertised_routes_cmd_bgpd;
extern struct cmd_element no_bgp_network_mask_cmd_bgpd;
extern struct cmd_element bgp_damp_unset_cmd_bgpd;
extern struct cmd_element no_aggregate_address_summary_only_cmd_bgpd;
extern struct cmd_element neighbor_capability_orf_prefix_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_external_ipv4_soft_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_instance_all_soft_out_cmd_bgpd;
extern struct cmd_element show_ip_bgp_neighbor_received_prefix_filter_cmd_bgpd;
extern struct cmd_element no_neighbor_set_peer_group_cmd_bgpd;
extern struct cmd_element bgp_network_mask_route_map_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_group_in_cmd_bgpd;
extern struct cmd_element aggregate_address_as_set_cmd_bgpd;
extern struct cmd_element clear_bgp_all_in_cmd_bgpd;
extern struct cmd_element bgp_damp_set_cmd_bgpd;
extern struct cmd_element no_neighbor_peer_group_remote_as_cmd_bgpd;
extern struct cmd_element no_dump_bgp_routes_cmd_bgpd;
extern struct cmd_element no_aggregate_address_mask_as_set_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_community4_cmd_bgpd;
extern struct cmd_element no_bgp_confederation_peers_cmd_bgpd;
extern struct cmd_element no_set_weight_val_cmd_bgpd;
extern struct cmd_element bgp_graceful_restart_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_community_list_exact_cmd_bgpd;
extern struct cmd_element no_match_metric_val_cmd_bgpd;
extern struct cmd_element show_ip_bgp_neighbor_prefix_counts_cmd_bgpd;
extern struct cmd_element bgp_scan_time_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_community3_exact_cmd_bgpd;
extern struct cmd_element no_set_aspath_prepend_val_cmd_bgpd;
extern struct cmd_element no_neighbor_attr_unchanged4_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_peer_vpnv4_in_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_external_soft_out_cmd_bgpd;
extern struct cmd_element show_bgp_instance_ipv6_neighbors_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_ipv4_in_prefix_filter_cmd_bgpd;
extern struct cmd_element neighbor_attr_unchanged5_cmd_bgpd;
extern struct cmd_element show_ip_bgp_instance_neighbors_cmd_bgpd;
extern struct cmd_element no_bgp_default_local_preference_val_cmd_bgpd;
extern struct cmd_element bgp_cluster_id_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_vpnv4_in_cmd_bgpd;
extern struct cmd_element bgp_redistribute_ipv4_metric_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_ipv4_soft_out_cmd_bgpd;
extern struct cmd_element set_ecommunity_soo_cmd_bgpd;
extern struct cmd_element bgp_network_import_check_cmd_bgpd;
extern struct cmd_element clear_bgp_instance_all_cmd_bgpd;
extern struct cmd_element clear_bgp_as_soft_in_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_peer_group_soft_out_cmd_bgpd;
extern struct cmd_element no_neighbor_timers_cmd_bgpd;
extern struct cmd_element bgp_cluster_id32_cmd_bgpd;
extern struct cmd_element bgp_always_compare_med_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_rsclient_summary_cmd_bgpd;
extern struct cmd_element aggregate_address_mask_summary_as_set_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_community3_cmd_bgpd;
extern struct cmd_element match_ip_next_hop_cmd_bgpd;
extern struct cmd_element neighbor_attr_unchanged2_cmd_bgpd;
extern struct cmd_element clear_bgp_all_soft_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_prefix_longer_cmd_bgpd;
extern struct cmd_element no_aggregate_address_mask_cmd_bgpd;
extern struct cmd_element no_bgp_deterministic_med_cmd_bgpd;
extern struct cmd_element show_ip_bgp_ipv4_community2_cmd_bgpd;
extern struct cmd_element no_match_ip_address_prefix_list_cmd_bgpd;
extern struct cmd_element match_pathlimit_as_cmd_bgpd;
extern struct cmd_element address_family_ipv4_cmd_bgpd;
extern struct cmd_element no_bgp_redistribute_ipv4_metric_rmap_cmd_bgpd;
extern struct cmd_element no_bgp_graceful_restart_stalepath_time_cmd_bgpd;
extern struct cmd_element ip_extcommunity_list_name_standard_cmd_bgpd;
extern struct cmd_element no_bgp_cluster_id_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_group_soft_in_cmd_bgpd;
extern struct cmd_element match_aspath_cmd_bgpd;
extern struct cmd_element neighbor_ebgp_multihop_cmd_bgpd;
extern struct cmd_element show_ip_bgp_community4_exact_cmd_bgpd;
extern struct cmd_element no_set_aspath_prepend_cmd_bgpd;
extern struct cmd_element clear_bgp_ipv6_all_in_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_all_soft_in_cmd_bgpd;
extern struct cmd_element ip_extcommunity_list_name_standard2_cmd_bgpd;
extern struct cmd_element ip_community_list_standard_cmd_bgpd;
extern struct cmd_element clear_bgp_all_soft_out_cmd_bgpd;
extern struct cmd_element no_neighbor_advertise_interval_val_cmd_bgpd;
extern struct cmd_element no_match_aspath_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_soft_in_cmd_bgpd;
extern struct cmd_element match_peer_cmd_bgpd;
extern struct cmd_element show_ip_bgp_instance_rsclient_summary_cmd_bgpd;
extern struct route_map_rule_cmd route_match_ecommunity_cmd_bgpd;
extern struct cmd_element neighbor_weight_cmd_bgpd;
extern struct cmd_element neighbor_capability_route_refresh_cmd_bgpd;
extern struct cmd_element clear_bgp_peer_group_in_prefix_filter_cmd_bgpd;
extern struct cmd_element bgp_distance_source_cmd_bgpd;
extern struct cmd_element bgp_damp_unset2_cmd_bgpd;
extern struct cmd_element clear_ip_bgp_as_vpnv4_soft_in_cmd_bgpd;
extern struct cmd_element no_ip_extcommunity_list_name_standard_cmd_bgpd;
extern struct cmd_element show_ip_bgp_view_rsclient_prefix_cmd_bgpd;
extern struct cmd_element no_neighbor_local_as_val_cmd_bgpd;
extern struct cmd_element no_ip_community_list_expanded_all_cmd_bgpd;
extern struct cmd_element no_neighbor_prefix_list_cmd_bgpd;
extern struct cmd_element no_bgp_timers_cmd_bgpd;
extern struct cmd_element bgp_network_route_map_cmd_bgpd;
extern struct cmd_element bgp_redistribute_ipv4_metric_rmap_cmd_bgpd;
extern struct cmd_element bgp_network_mask_backdoor_ttl_cmd_bgpd;
extern struct cmd_element show_ip_bgp_neighbor_damp_cmd_bgpd;
extern struct cmd_element show_bgp_route_map_cmd_bgpd;
extern struct cmd_element neighbor_nexthop_self_cmd_bgpd;

void GlobalVars_initializeActiveSet_bgpd()
{
	struct peer_flag_action peer_flag_action_list__T[] =  
  {
    { PEER_FLAG_PASSIVE,                  0, peer_change_reset },
    { PEER_FLAG_SHUTDOWN,                 0, peer_change_reset },
    { PEER_FLAG_DONT_CAPABILITY,          0, peer_change_none },
    { PEER_FLAG_OVERRIDE_CAPABILITY,      0, peer_change_none },
    { PEER_FLAG_STRICT_CAP_MATCH,         0, peer_change_none },
    { PEER_FLAG_DYNAMIC_CAPABILITY,       0, peer_change_reset },
    { PEER_FLAG_DISABLE_CONNECTED_CHECK,  0, peer_change_reset },
    { 0, 0, 0 }
  };
	struct message orf_type_str__T[] = 
{
  { ORF_TYPE_PREFIX,		"Prefixlist"		},
  { ORF_TYPE_PREFIX_OLD,	"Prefixlist (old)"	},
};
	struct cmd_node as_list_node__T = 
{
  AS_LIST_NODE,
  "",
  1
};
	struct cmd_node bgp_node__T = 
{
  BGP_NODE,
  "%s(config-router)# ",
  1,
};
	size_t cap_minsizes__T[] =  
{
  [CAPABILITY_CODE_MP]		= sizeof (struct capability_mp_data),
  [CAPABILITY_CODE_REFRESH]	= CAPABILITY_CODE_REFRESH_LEN,
  [CAPABILITY_CODE_ORF]		= sizeof (struct capability_orf_entry),
  [CAPABILITY_CODE_RESTART]	= sizeof (struct capability_gr),
  [CAPABILITY_CODE_AS4]		= CAPABILITY_CODE_AS4_LEN,
  [CAPABILITY_CODE_DYNAMIC]	= CAPABILITY_CODE_DYNAMIC_LEN,
  [CAPABILITY_CODE_REFRESH_OLD]	= CAPABILITY_CODE_REFRESH_LEN,
  [CAPABILITY_CODE_ORF_OLD]	= sizeof (struct capability_orf_entry),
};
	struct cmd_node debug_node__T = 
{
  DEBUG_NODE,
  "",
  1
};
	struct cmd_node community_list_node__T = 
{
  COMMUNITY_LIST_NODE,
  "",
  1				
};
	struct_as_list_master as_list_master__T = 
{
  {NULL, NULL},
  {NULL, NULL},
  NULL,
  NULL
};
	struct peer_flag_action peer_af_flag_action_list__T[] =  
  {
    { PEER_FLAG_NEXTHOP_SELF,             1, peer_change_reset_out },
    { PEER_FLAG_SEND_COMMUNITY,           1, peer_change_reset_out },
    { PEER_FLAG_SEND_EXT_COMMUNITY,       1, peer_change_reset_out },
    { PEER_FLAG_SOFT_RECONFIG,            0, peer_change_reset_in },
    { PEER_FLAG_REFLECTOR_CLIENT,         1, peer_change_reset },
    { PEER_FLAG_RSERVER_CLIENT,           1, peer_change_reset },
    { PEER_FLAG_AS_PATH_UNCHANGED,        1, peer_change_reset_out },
    { PEER_FLAG_NEXTHOP_UNCHANGED,        1, peer_change_reset_out },
    { PEER_FLAG_MED_UNCHANGED,            1, peer_change_reset_out },
    { PEER_FLAG_REMOVE_PRIVATE_AS,        1, peer_change_reset_out },
    { PEER_FLAG_ALLOWAS_IN,               0, peer_change_reset_in },
    { PEER_FLAG_ORF_PREFIX_SM,            1, peer_change_reset },
    { PEER_FLAG_ORF_PREFIX_RM,            1, peer_change_reset },
    { PEER_FLAG_NEXTHOP_LOCAL_UNCHANGED,  0, peer_change_reset_out },
    { 0, 0, 0 }
  };
	struct message capcode_str__T[] = 
{
  { CAPABILITY_CODE_MP,			"MultiProtocol Extensions"	},
  { CAPABILITY_CODE_REFRESH,		"Route Refresh"			},
  { CAPABILITY_CODE_ORF,		"Cooperative Route Filtering" 	},
  { CAPABILITY_CODE_RESTART,		"Graceful Restart"		},
  { CAPABILITY_CODE_AS4,		"4-octet AS number"		},
  { CAPABILITY_CODE_DYNAMIC,		"Dynamic"			},
  { CAPABILITY_CODE_REFRESH_OLD,	"Route Refresh (Old)"		},
  { CAPABILITY_CODE_ORF_OLD,		"ORF (Old)"			},
};
	struct cmd_node bgp_vpnv4_node__T = 
{
  BGP_VPNV4_NODE,
  "%s(config-router-af)# ",
  1
};
	struct cmd_node bgp_ipv4_unicast_node__T = 
{
  BGP_IPV4_NODE,
  "%s(config-router-af)# ",
  1,
};
	struct cmd_node bgp_ipv6_multicast_node__T = 
{
  BGP_IPV6M_NODE,
  "%s(config-router-af)# ",
  1,
};
	struct cmd_node bgp_dump_node__T = 
{
  DUMP_NODE,
  "",
  1
};
	struct message orf_mode_str__T[] = 
{
  { ORF_MODE_RECEIVE,	"Receive"	},
  { ORF_MODE_SEND,	"Send"		},
  { ORF_MODE_BOTH,	"Both"		},
};
	const char * pcount_strs__T[] = 
{
  [PCOUNT_ADJ_IN]  = "Adj-in",
  [PCOUNT_DAMPED]  = "Damped",
  [PCOUNT_REMOVED] = "Removed",
  [PCOUNT_HISTORY] = "History",
  [PCOUNT_STALE]   = "Stale",
  [PCOUNT_VALID]   = "Valid",
  [PCOUNT_ALL]     = "All RIB",
  [PCOUNT_COUNTED] = "PfxCt counted",
  [PCOUNT_PFCNT]   = "Useable",
  [PCOUNT_MAX]     = NULL,
};
	struct cmd_node bgp_ipv6_unicast_node__T =  
{
  BGP_IPV6_NODE,
  "%s(config-router-af)# ",
  1,
};
	struct cmd_node bgp_ipv4_multicast_node__T = 
{
  BGP_IPV4M_NODE,
  "%s(config-router-af)# ",
  1,
};
	const char * table_stats_strs__T[] = 
{
  [BGP_STATS_PREFIXES]            = "Total Prefixes",
  [BGP_STATS_TOTPLEN]             = "Average prefix length",
  [BGP_STATS_RIB]                 = "Total Advertisements",
  [BGP_STATS_UNAGGREGATEABLE]     = "Unaggregateable prefixes",
  [BGP_STATS_MAX_AGGREGATEABLE]   = "Maximum aggregateable prefixes",
  [BGP_STATS_AGGREGATES]          = "BGP Aggregate advertisements",
  [BGP_STATS_SPACE]               = "Address space advertised",
  [BGP_STATS_ASPATH_COUNT]        = "Advertisements with paths",
  [BGP_STATS_ASPATH_MAXHOPS]      = "Longest AS-Path (hops)",
  [BGP_STATS_ASPATH_MAXSIZE]      = "Largest AS-Path (bytes)",
  [BGP_STATS_ASPATH_TOTHOPS]      = "Average AS-Path length (hops)",
  [BGP_STATS_ASPATH_TOTSIZE]      = "Average AS-Path size (bytes)",
  [BGP_STATS_ASN_HIGHEST]         = "Highest public ASN",
  [BGP_STATS_MAX] = NULL,
};
	memcpy(&__activeVars->no_neighbor_attr_unchanged1_cmd__X, &no_neighbor_attr_unchanged1_cmd_bgpd, sizeof(no_neighbor_attr_unchanged1_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_cmd__X, &bgp_network_cmd_bgpd, sizeof(bgp_network_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_peer_in_prefix_filter_cmd__X, &clear_bgp_peer_in_prefix_filter_cmd_bgpd, sizeof(clear_bgp_peer_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_ttl_cmd__X, &no_bgp_network_ttl_cmd_bgpd, sizeof(no_bgp_network_ttl_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_scan_cmd__X, &show_ip_bgp_scan_cmd_bgpd, sizeof(show_ip_bgp_scan_cmd_bgpd));
	memcpy(&__activeVars->no_match_ip_route_source_val_cmd__X, &no_match_ip_route_source_val_cmd_bgpd, sizeof(no_match_ip_route_source_val_cmd_bgpd));
	memcpy(&__activeVars->show_ip_community_list_arg_cmd__X, &show_ip_community_list_arg_cmd_bgpd, sizeof(show_ip_community_list_arg_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_distribute_list_cmd__X, &no_neighbor_distribute_list_cmd_bgpd, sizeof(no_neighbor_distribute_list_cmd_bgpd));
	memcpy(&__activeVars->bgp_default_local_preference_cmd__X, &bgp_default_local_preference_cmd_bgpd, sizeof(bgp_default_local_preference_cmd_bgpd));
	memcpy(&__activeVars->no_debug_bgp_as4_cmd__X, &no_debug_bgp_as4_cmd_bgpd, sizeof(no_debug_bgp_as4_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_ipv4_soft_in_cmd__X, &clear_ip_bgp_all_ipv4_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_all_ipv4_soft_in_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_maximum_prefix_cmd__X, &no_neighbor_maximum_prefix_cmd_bgpd, sizeof(no_neighbor_maximum_prefix_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_mask_natural_backdoor_cmd__X, &bgp_network_mask_natural_backdoor_cmd_bgpd, sizeof(bgp_network_mask_natural_backdoor_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_attr_unchanged9_cmd__X, &no_neighbor_attr_unchanged9_cmd_bgpd, sizeof(no_neighbor_attr_unchanged9_cmd_bgpd));
	memcpy(&__activeVars->no_set_community_val_cmd__X, &no_set_community_val_cmd_bgpd, sizeof(no_set_community_val_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_instance_all_soft_cmd__X, &clear_ip_bgp_instance_all_soft_cmd_bgpd, sizeof(clear_ip_bgp_instance_all_soft_cmd_bgpd));
	memcpy(&__activeVars->neighbor_prefix_list_cmd__X, &neighbor_prefix_list_cmd_bgpd, sizeof(neighbor_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->undebug_bgp_fsm_cmd__X, &undebug_bgp_fsm_cmd_bgpd, sizeof(undebug_bgp_fsm_cmd_bgpd));
	memcpy(&__activeVars->no_match_peer_cmd__X, &no_match_peer_cmd_bgpd, sizeof(no_match_peer_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_neighbor_received_routes_cmd__X, &show_ip_bgp_neighbor_received_routes_cmd_bgpd, sizeof(show_ip_bgp_neighbor_received_routes_cmd_bgpd));
	memcpy(&__activeVars->dump_bgp_all_cmd__X, &dump_bgp_all_cmd_bgpd, sizeof(dump_bgp_all_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_route_map_cmd__X, &no_bgp_network_route_map_cmd_bgpd, sizeof(no_bgp_network_route_map_cmd_bgpd));
	memcpy(&__activeVars->no_match_origin_val_cmd__X, &no_match_origin_val_cmd_bgpd, sizeof(no_match_origin_val_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_neighbor_received_routes_cmd__X, &show_ip_bgp_ipv4_neighbor_received_routes_cmd_bgpd, sizeof(show_ip_bgp_ipv4_neighbor_received_routes_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_peer_soft_out_cmd__X, &clear_bgp_peer_soft_out_cmd_bgpd, sizeof(clear_bgp_peer_soft_out_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_graceful_restart_cmd__X, &no_bgp_graceful_restart_cmd_bgpd, sizeof(no_bgp_graceful_restart_cmd_bgpd));
	memcpy(&__activeVars->no_router_bgp_cmd__X, &no_router_bgp_cmd_bgpd, sizeof(no_router_bgp_cmd_bgpd));
	__activeVars->vty_addr__X =  NULL;
	memcpy(&__activeVars->route_set_pathlimit_ttl_cmd__X, &route_set_pathlimit_ttl_cmd_bgpd, sizeof(route_set_pathlimit_ttl_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_all_cmd__X, &clear_bgp_all_cmd_bgpd, sizeof(clear_bgp_all_cmd_bgpd));
	memcpy(&__activeVars->address_family_ipv4_safi_cmd__X, &address_family_ipv4_safi_cmd_bgpd, sizeof(address_family_ipv4_safi_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_default_originate_rmap_cmd__X, &no_neighbor_default_originate_rmap_cmd_bgpd, sizeof(no_neighbor_default_originate_rmap_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_summary_cmd__X, &show_ip_bgp_ipv4_summary_cmd_bgpd, sizeof(show_ip_bgp_ipv4_summary_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_rd_summary_cmd__X, &show_ip_bgp_vpnv4_rd_summary_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_rd_summary_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_in_cmd__X, &clear_ip_bgp_as_in_cmd_bgpd, sizeof(clear_ip_bgp_as_in_cmd_bgpd));
	memcpy(&__activeVars->show_debugging_bgp_cmd__X, &show_debugging_bgp_cmd_bgpd, sizeof(show_debugging_bgp_cmd_bgpd));
	memcpy(&__activeVars->peer_flag_action_list__X, &peer_flag_action_list__T, sizeof(peer_flag_action_list__T));
	memcpy(&__activeVars->clear_ip_bgp_external_ipv4_out_cmd__X, &clear_ip_bgp_external_ipv4_out_cmd_bgpd, sizeof(clear_ip_bgp_external_ipv4_out_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_timers_connect_val_cmd__X, &no_neighbor_timers_connect_val_cmd_bgpd, sizeof(no_neighbor_timers_connect_val_cmd_bgpd));
	__activeVars->bgp_notify_cease_msg_max__X =  BGP_NOTIFY_CEASE_MAX;
	memcpy(&__activeVars->clear_ip_bgp_peer_soft_cmd__X, &clear_ip_bgp_peer_soft_cmd_bgpd, sizeof(clear_ip_bgp_peer_soft_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_attr_unchanged3_cmd__X, &no_neighbor_attr_unchanged3_cmd_bgpd, sizeof(no_neighbor_attr_unchanged3_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_mask_backdoor_ttl_cmd__X, &no_bgp_network_mask_backdoor_ttl_cmd_bgpd, sizeof(no_bgp_network_mask_backdoor_ttl_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_in_cmd__X, &clear_ip_bgp_peer_in_cmd_bgpd, sizeof(clear_ip_bgp_peer_in_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_soft_in_cmd__X, &clear_bgp_ipv6_peer_soft_in_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_soft_in_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_summary_cmd__X, &show_ip_bgp_summary_cmd_bgpd, sizeof(show_ip_bgp_summary_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_in_cmd__X, &clear_bgp_ipv6_peer_in_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_in_cmd_bgpd));
	memcpy(&__activeVars->orf_type_str__X, &orf_type_str__T, sizeof(orf_type_str__T));
	memcpy(&__activeVars->neighbor_allowas_in_arg_cmd__X, &neighbor_allowas_in_arg_cmd_bgpd, sizeof(neighbor_allowas_in_arg_cmd_bgpd));
	memcpy(&__activeVars->route_set_metric_cmd__X, &route_set_metric_cmd_bgpd, sizeof(route_set_metric_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_instance_ipv4_rsclient_summary_cmd__X, &show_ip_bgp_instance_ipv4_rsclient_summary_cmd_bgpd, sizeof(show_ip_bgp_instance_ipv4_rsclient_summary_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_group_soft_in_cmd__X, &clear_bgp_ipv6_peer_group_soft_in_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_group_soft_in_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_capability_route_refresh_cmd__X, &no_neighbor_capability_route_refresh_cmd_bgpd, sizeof(no_neighbor_capability_route_refresh_cmd_bgpd));
	memcpy(&__activeVars->neighbor_ebgp_multihop_ttl_cmd__X, &neighbor_ebgp_multihop_ttl_cmd_bgpd, sizeof(neighbor_ebgp_multihop_ttl_cmd_bgpd));
	memcpy(&__activeVars->no_debug_bgp_keepalive_cmd__X, &no_debug_bgp_keepalive_cmd_bgpd, sizeof(no_debug_bgp_keepalive_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_view_prefix_cmd__X, &show_ip_bgp_view_prefix_cmd_bgpd, sizeof(show_ip_bgp_view_prefix_cmd_bgpd));
	memcpy(&__activeVars->bgp_deterministic_med_cmd__X, &bgp_deterministic_med_cmd_bgpd, sizeof(bgp_deterministic_med_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_peer_group_out_cmd__X, &clear_bgp_peer_group_out_cmd_bgpd, sizeof(clear_bgp_peer_group_out_cmd_bgpd));
	memcpy(&__activeVars->undebug_bgp_as4_cmd__X, &undebug_bgp_as4_cmd_bgpd, sizeof(undebug_bgp_as4_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_filter_list_cmd__X, &show_ip_bgp_filter_list_cmd_bgpd, sizeof(show_ip_bgp_filter_list_cmd_bgpd));
	memcpy(&__activeVars->no_vpnv4_network_cmd__X, &no_vpnv4_network_cmd_bgpd, sizeof(no_vpnv4_network_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_rd_route_cmd__X, &show_ip_bgp_vpnv4_rd_route_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_rd_route_cmd_bgpd));
	memcpy(&__activeVars->as_list_node__X, &as_list_node__T, sizeof(as_list_node__T));
	memcpy(&__activeVars->undebug_bgp_keepalive_cmd__X, &undebug_bgp_keepalive_cmd_bgpd, sizeof(undebug_bgp_keepalive_cmd_bgpd));
	__activeVars->capcode_str_max__X =  sizeof(capcode_str)/sizeof(capcode_str[0]);
	memcpy(&__activeVars->no_neighbor_attr_unchanged5_cmd__X, &no_neighbor_attr_unchanged5_cmd_bgpd, sizeof(no_neighbor_attr_unchanged5_cmd_bgpd));
	memcpy(&__activeVars->aggregate_address_summary_only_cmd__X, &aggregate_address_summary_only_cmd_bgpd, sizeof(aggregate_address_summary_only_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_ipv4_soft_in_cmd__X, &clear_ip_bgp_peer_ipv4_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_peer_ipv4_soft_in_cmd_bgpd));
	memcpy(&__activeVars->no_set_pathlimit_ttl_val_cmd__X, &no_set_pathlimit_ttl_val_cmd_bgpd, sizeof(no_set_pathlimit_ttl_val_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_vpnv4_soft_out_cmd__X, &clear_ip_bgp_all_vpnv4_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_all_vpnv4_soft_out_cmd_bgpd));
	memcpy(&__activeVars->route_match_ip_route_source_cmd__X, &route_match_ip_route_source_cmd_bgpd, sizeof(route_match_ip_route_source_cmd_bgpd));
	memcpy(&__activeVars->no_set_origin_val_cmd__X, &no_set_origin_val_cmd_bgpd, sizeof(no_set_origin_val_cmd_bgpd));
	memcpy(&__activeVars->debug_bgp_as4_cmd__X, &debug_bgp_as4_cmd_bgpd, sizeof(debug_bgp_as4_cmd_bgpd));
	memcpy(&__activeVars->bgp_node__X, &bgp_node__T, sizeof(bgp_node__T));
	memcpy(&__activeVars->bgp_confederation_identifier_cmd__X, &bgp_confederation_identifier_cmd_bgpd, sizeof(bgp_confederation_identifier_cmd_bgpd));
	memcpy(&__activeVars->route_set_atomic_aggregate_cmd__X, &route_set_atomic_aggregate_cmd_bgpd, sizeof(route_set_atomic_aggregate_cmd_bgpd));
	memcpy(&__activeVars->route_set_community_cmd__X, &route_set_community_cmd_bgpd, sizeof(route_set_community_cmd_bgpd));
	memcpy(&__activeVars->debug_bgp_update_direct_cmd__X, &debug_bgp_update_direct_cmd_bgpd, sizeof(debug_bgp_update_direct_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_flap_filter_list_cmd__X, &show_ip_bgp_flap_filter_list_cmd_bgpd, sizeof(show_ip_bgp_flap_filter_list_cmd_bgpd));
	memcpy(&__activeVars->bgp_damp_set3_cmd__X, &bgp_damp_set3_cmd_bgpd, sizeof(bgp_damp_set3_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_mask_natural_route_map_cmd__X, &bgp_network_mask_natural_route_map_cmd_bgpd, sizeof(bgp_network_mask_natural_route_map_cmd_bgpd));
	memcpy(&__activeVars->cap_minsizes__X, &cap_minsizes__T, sizeof(cap_minsizes__T));
	memcpy(&__activeVars->clear_ip_bgp_as_vpnv4_soft_out_cmd__X, &clear_ip_bgp_as_vpnv4_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_as_vpnv4_soft_out_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_remote_as_cmd__X, &no_neighbor_remote_as_cmd_bgpd, sizeof(no_neighbor_remote_as_cmd_bgpd));
	memcpy(&__activeVars->set_vpnv4_nexthop_cmd__X, &set_vpnv4_nexthop_cmd_bgpd, sizeof(set_vpnv4_nexthop_cmd_bgpd));
	memcpy(&__activeVars->match_community_exact_cmd__X, &match_community_exact_cmd_bgpd, sizeof(match_community_exact_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_rsclient_summary_cmd__X, &show_ip_bgp_rsclient_summary_cmd_bgpd, sizeof(show_ip_bgp_rsclient_summary_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_neighbors_peer_cmd__X, &show_bgp_neighbors_peer_cmd_bgpd, sizeof(show_bgp_neighbors_peer_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_all_neighbors_cmd__X, &show_ip_bgp_vpnv4_all_neighbors_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_all_neighbors_cmd_bgpd));
	memcpy(&__activeVars->neighbor_send_community_cmd__X, &neighbor_send_community_cmd_bgpd, sizeof(neighbor_send_community_cmd_bgpd));
	memcpy(&__activeVars->no_set_pathlimit_ttl_cmd__X, &no_set_pathlimit_ttl_cmd_bgpd, sizeof(no_set_pathlimit_ttl_cmd_bgpd));
	memcpy(&__activeVars->neighbor_route_reflector_client_cmd__X, &neighbor_route_reflector_client_cmd_bgpd, sizeof(neighbor_route_reflector_client_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_soft_cmd__X, &clear_ip_bgp_all_soft_cmd_bgpd, sizeof(clear_ip_bgp_all_soft_cmd_bgpd));
	memcpy(&__activeVars->dump_bgp_updates_cmd__X, &dump_bgp_updates_cmd_bgpd, sizeof(dump_bgp_updates_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_in_prefix_filter_cmd__X, &clear_ip_bgp_peer_in_prefix_filter_cmd_bgpd, sizeof(clear_ip_bgp_peer_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_community_list_exact_cmd__X, &show_ip_bgp_community_list_exact_cmd_bgpd, sizeof(show_ip_bgp_community_list_exact_cmd_bgpd));
	memcpy(&__activeVars->route_set_vpnv4_nexthop_cmd__X, &route_set_vpnv4_nexthop_cmd_bgpd, sizeof(route_set_vpnv4_nexthop_cmd_bgpd));
	memcpy(&__activeVars->ip_extcommunity_list_standard_cmd__X, &ip_extcommunity_list_standard_cmd_bgpd, sizeof(ip_extcommunity_list_standard_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_mask_ttl_cmd__X, &bgp_network_mask_ttl_cmd_bgpd, sizeof(bgp_network_mask_ttl_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_filter_list_cmd__X, &no_neighbor_filter_list_cmd_bgpd, sizeof(no_neighbor_filter_list_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_config_type_cmd__X, &no_bgp_config_type_cmd_bgpd, sizeof(no_bgp_config_type_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_all_soft_out_cmd__X, &clear_bgp_ipv6_all_soft_out_cmd_bgpd, sizeof(clear_bgp_ipv6_all_soft_out_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_bestpath_med2_cmd__X, &no_bgp_bestpath_med2_cmd_bgpd, sizeof(no_bgp_bestpath_med2_cmd_bgpd));
	memcpy(&__activeVars->route_set_ip_nexthop_cmd__X, &route_set_ip_nexthop_cmd_bgpd, sizeof(route_set_ip_nexthop_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_multiple_instance_cmd__X, &no_bgp_multiple_instance_cmd_bgpd, sizeof(no_bgp_multiple_instance_cmd_bgpd));
	memcpy(&__activeVars->no_debug_bgp_events_cmd__X, &no_debug_bgp_events_cmd_bgpd, sizeof(no_debug_bgp_events_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_ipv4_soft_cmd__X, &clear_ip_bgp_as_ipv4_soft_cmd_bgpd, sizeof(clear_ip_bgp_as_ipv4_soft_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_group_cmd__X, &clear_bgp_ipv6_peer_group_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_group_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_port_val_cmd__X, &no_neighbor_port_val_cmd_bgpd, sizeof(no_neighbor_port_val_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_community3_exact_cmd__X, &show_ip_bgp_community3_exact_cmd_bgpd, sizeof(show_ip_bgp_community3_exact_cmd_bgpd));
	memcpy(&__activeVars->route_match_pathlimit_as_cmd__X, &route_match_pathlimit_as_cmd_bgpd, sizeof(route_match_pathlimit_as_cmd_bgpd));
	memcpy(&__activeVars->no_match_ip_route_source_prefix_list_cmd__X, &no_match_ip_route_source_prefix_list_cmd_bgpd, sizeof(no_match_ip_route_source_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->bgp_distance_source_access_list_cmd__X, &bgp_distance_source_access_list_cmd_bgpd, sizeof(bgp_distance_source_access_list_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_community3_cmd__X, &show_ip_bgp_community3_cmd_bgpd, sizeof(show_ip_bgp_community3_cmd_bgpd));
	memcpy(&__activeVars->ip_community_list_name_standard2_cmd__X, &ip_community_list_name_standard2_cmd_bgpd, sizeof(ip_community_list_name_standard2_cmd_bgpd));
	memcpy(&__activeVars->ip_extcommunity_list_name_expanded_cmd__X, &ip_extcommunity_list_name_expanded_cmd_bgpd, sizeof(ip_extcommunity_list_name_expanded_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_as_cmd__X, &clear_bgp_as_cmd_bgpd, sizeof(clear_bgp_as_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_neighbor_prefix_counts_cmd__X, &show_ip_bgp_vpnv4_neighbor_prefix_counts_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_neighbor_prefix_counts_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_peer_group_cmd__X, &clear_bgp_peer_group_cmd_bgpd, sizeof(clear_bgp_peer_group_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_nexthop_local_unchanged_cmd__X, &no_neighbor_nexthop_local_unchanged_cmd_bgpd, sizeof(no_neighbor_nexthop_local_unchanged_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_rsclient_cmd__X, &show_ip_bgp_rsclient_cmd_bgpd, sizeof(show_ip_bgp_rsclient_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_statistics_cmd__X, &show_bgp_statistics_cmd_bgpd, sizeof(show_bgp_statistics_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_community_cmd__X, &show_ip_bgp_community_cmd_bgpd, sizeof(show_ip_bgp_community_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_statistics_vpnv4_cmd__X, &show_bgp_statistics_vpnv4_cmd_bgpd, sizeof(show_bgp_statistics_vpnv4_cmd_bgpd));
	memcpy(&__activeVars->neighbor_maximum_prefix_threshold_cmd__X, &neighbor_maximum_prefix_threshold_cmd_bgpd, sizeof(neighbor_maximum_prefix_threshold_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_statistics_view_cmd__X, &show_bgp_statistics_view_cmd_bgpd, sizeof(show_bgp_statistics_view_cmd_bgpd));
	memcpy(&__activeVars->route_set_ecommunity_rt_cmd__X, &route_set_ecommunity_rt_cmd_bgpd, sizeof(route_set_ecommunity_rt_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_neighbor_received_prefix_filter_cmd__X, &show_ip_bgp_ipv4_neighbor_received_prefix_filter_cmd_bgpd, sizeof(show_ip_bgp_ipv4_neighbor_received_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->neighbor_maximum_prefix_cmd__X, &neighbor_maximum_prefix_cmd_bgpd, sizeof(neighbor_maximum_prefix_cmd_bgpd));
	memcpy(&__activeVars->no_set_ecommunity_rt_cmd__X, &no_set_ecommunity_rt_cmd_bgpd, sizeof(no_set_ecommunity_rt_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_instance_all_ipv4_soft_in_cmd__X, &clear_ip_bgp_instance_all_ipv4_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_instance_all_ipv4_soft_in_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_in_prefix_filter_cmd__X, &clear_bgp_ipv6_peer_in_prefix_filter_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_all_cmd__X, &clear_bgp_ipv6_all_cmd_bgpd, sizeof(clear_bgp_ipv6_all_cmd_bgpd));
	memcpy(&__activeVars->router_bgp_view_cmd__X, &router_bgp_view_cmd_bgpd, sizeof(router_bgp_view_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_community_all_cmd__X, &show_ip_bgp_ipv4_community_all_cmd_bgpd, sizeof(show_ip_bgp_ipv4_community_all_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_as_soft_cmd__X, &clear_bgp_as_soft_cmd_bgpd, sizeof(clear_bgp_as_soft_cmd_bgpd));
	memcpy(&__activeVars->no_ip_community_list_name_expanded_all_cmd__X, &no_ip_community_list_name_expanded_all_cmd_bgpd, sizeof(no_ip_community_list_name_expanded_all_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_ipv4_out_cmd__X, &clear_ip_bgp_all_ipv4_out_cmd_bgpd, sizeof(clear_ip_bgp_all_ipv4_out_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_route_server_client_cmd__X, &no_neighbor_route_server_client_cmd_bgpd, sizeof(no_neighbor_route_server_client_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_distance_source_access_list_cmd__X, &no_bgp_distance_source_access_list_cmd_bgpd, sizeof(no_bgp_distance_source_access_list_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_confederation_identifier_cmd__X, &no_bgp_confederation_identifier_cmd_bgpd, sizeof(no_bgp_confederation_identifier_cmd_bgpd));
	memcpy(&__activeVars->neighbor_update_source_cmd__X, &neighbor_update_source_cmd_bgpd, sizeof(neighbor_update_source_cmd_bgpd));
	memcpy(&__activeVars->no_set_ecommunity_soo_cmd__X, &no_set_ecommunity_soo_cmd_bgpd, sizeof(no_set_ecommunity_soo_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_neighbors_cmd__X, &show_ip_bgp_ipv4_neighbors_cmd_bgpd, sizeof(show_ip_bgp_ipv4_neighbors_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_ipv4_soft_out_cmd__X, &clear_ip_bgp_peer_ipv4_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_peer_ipv4_soft_out_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_vpnv4_soft_cmd__X, &clear_ip_bgp_all_vpnv4_soft_cmd_bgpd, sizeof(clear_ip_bgp_all_vpnv4_soft_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_out_cmd__X, &clear_ip_bgp_all_out_cmd_bgpd, sizeof(clear_ip_bgp_all_out_cmd_bgpd));
	__activeVars->bgp_notify_capability_msg_max__X =  BGP_NOTIFY_CAPABILITY_MAX;
	memcpy(&__activeVars->no_neighbor_ebgp_multihop_ttl_cmd__X, &no_neighbor_ebgp_multihop_ttl_cmd_bgpd, sizeof(no_neighbor_ebgp_multihop_ttl_cmd_bgpd));
	memcpy(&__activeVars->bgp_redistribute_ipv4_cmd__X, &bgp_redistribute_ipv4_cmd_bgpd, sizeof(bgp_redistribute_ipv4_cmd_bgpd));
	memcpy(&__activeVars->neighbor_maximum_prefix_threshold_warning_cmd__X, &neighbor_maximum_prefix_threshold_warning_cmd_bgpd, sizeof(neighbor_maximum_prefix_threshold_warning_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_interface_cmd__X, &no_neighbor_interface_cmd_bgpd, sizeof(no_neighbor_interface_cmd_bgpd));
	memcpy(&__activeVars->debug_node__X, &debug_node__T, sizeof(debug_node__T));
	memcpy(&__activeVars->neighbor_peer_group_cmd__X, &neighbor_peer_group_cmd_bgpd, sizeof(neighbor_peer_group_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_ipv4_in_prefix_filter_cmd__X, &clear_ip_bgp_peer_ipv4_in_prefix_filter_cmd_bgpd, sizeof(clear_ip_bgp_peer_ipv4_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_flap_cidr_only_cmd__X, &show_ip_bgp_flap_cidr_only_cmd_bgpd, sizeof(show_ip_bgp_flap_cidr_only_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_all_summary_cmd__X, &show_ip_bgp_vpnv4_all_summary_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_all_summary_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_external_cmd__X, &clear_bgp_external_cmd_bgpd, sizeof(clear_bgp_external_cmd_bgpd));
	memcpy(&__activeVars->address_family_vpnv4_cmd__X, &address_family_vpnv4_cmd_bgpd, sizeof(address_family_vpnv4_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_router_id_cmd__X, &no_bgp_router_id_cmd_bgpd, sizeof(no_bgp_router_id_cmd_bgpd));
	memcpy(&__activeVars->set_metric_addsub_cmd__X, &set_metric_addsub_cmd_bgpd, sizeof(set_metric_addsub_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_external_soft_cmd__X, &clear_bgp_external_soft_cmd_bgpd, sizeof(clear_bgp_external_soft_cmd_bgpd));
	memcpy(&__activeVars->address_family_vpnv4_unicast_cmd__X, &address_family_vpnv4_unicast_cmd_bgpd, sizeof(address_family_vpnv4_unicast_cmd_bgpd));
	memcpy(&__activeVars->show_ip_as_path_access_list_all_cmd__X, &show_ip_as_path_access_list_all_cmd_bgpd, sizeof(show_ip_as_path_access_list_all_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_attr_unchanged_cmd__X, &no_neighbor_attr_unchanged_cmd_bgpd, sizeof(no_neighbor_attr_unchanged_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_shutdown_cmd__X, &no_neighbor_shutdown_cmd_bgpd, sizeof(no_neighbor_shutdown_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_external_soft_in_cmd__X, &clear_ip_bgp_external_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_external_soft_in_cmd_bgpd));
	memcpy(&__activeVars->set_community_none_cmd__X, &set_community_none_cmd_bgpd, sizeof(set_community_none_cmd_bgpd));
	memcpy(&__activeVars->match_ip_route_source_prefix_list_cmd__X, &match_ip_route_source_prefix_list_cmd_bgpd, sizeof(match_ip_route_source_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->neighbor_attr_unchanged6_cmd__X, &neighbor_attr_unchanged6_cmd_bgpd, sizeof(neighbor_attr_unchanged6_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_as_cmd__X, &clear_bgp_ipv6_as_cmd_bgpd, sizeof(clear_bgp_ipv6_as_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_rd_neighbors_peer_cmd__X, &show_ip_bgp_vpnv4_rd_neighbors_peer_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_rd_neighbors_peer_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_peer_group_soft_out_cmd__X, &clear_bgp_peer_group_soft_out_cmd_bgpd, sizeof(clear_bgp_peer_group_soft_out_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_ebgp_multihop_cmd__X, &no_neighbor_ebgp_multihop_cmd_bgpd, sizeof(no_neighbor_ebgp_multihop_cmd_bgpd));
	memcpy(&__activeVars->no_aggregate_address_as_set_cmd__X, &no_aggregate_address_as_set_cmd_bgpd, sizeof(no_aggregate_address_as_set_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_instance_all_ipv4_soft_out_cmd__X, &clear_ip_bgp_instance_all_ipv4_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_instance_all_ipv4_soft_out_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_all_out_cmd__X, &clear_bgp_ipv6_all_out_cmd_bgpd, sizeof(clear_bgp_ipv6_all_out_cmd_bgpd));
	memcpy(&__activeVars->bgp_config_type_cmd__X, &bgp_config_type_cmd_bgpd, sizeof(bgp_config_type_cmd_bgpd));
	memcpy(&__activeVars->neighbor_attr_unchanged10_cmd__X, &neighbor_attr_unchanged10_cmd_bgpd, sizeof(neighbor_attr_unchanged10_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_backdoor_cmd__X, &no_bgp_network_backdoor_cmd_bgpd, sizeof(no_bgp_network_backdoor_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_soft_cmd__X, &clear_ip_bgp_as_soft_cmd_bgpd, sizeof(clear_ip_bgp_as_soft_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_external_soft_cmd__X, &clear_ip_bgp_external_soft_cmd_bgpd, sizeof(clear_ip_bgp_external_soft_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_ipv4_in_cmd__X, &clear_ip_bgp_as_ipv4_in_cmd_bgpd, sizeof(clear_ip_bgp_as_ipv4_in_cmd_bgpd));
	memcpy(&__activeVars->aggregate_address_mask_summary_only_cmd__X, &aggregate_address_mask_summary_only_cmd_bgpd, sizeof(aggregate_address_mask_summary_only_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_community_all_cmd__X, &show_ip_bgp_community_all_cmd_bgpd, sizeof(show_ip_bgp_community_all_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_attr_unchanged8_cmd__X, &no_neighbor_attr_unchanged8_cmd_bgpd, sizeof(no_neighbor_attr_unchanged8_cmd_bgpd));
	memcpy(&__activeVars->no_aggregate_address_cmd__X, &no_aggregate_address_cmd_bgpd, sizeof(no_aggregate_address_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_soft_out_cmd__X, &clear_ip_bgp_as_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_as_soft_out_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_view_cmd__X, &show_ip_bgp_view_cmd_bgpd, sizeof(show_ip_bgp_view_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_rd_neighbors_cmd__X, &show_ip_bgp_vpnv4_rd_neighbors_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_rd_neighbors_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_allowas_in_cmd__X, &no_neighbor_allowas_in_cmd_bgpd, sizeof(no_neighbor_allowas_in_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_ipv4_in_prefix_filter_cmd__X, &clear_ip_bgp_all_ipv4_in_prefix_filter_cmd_bgpd, sizeof(clear_ip_bgp_all_ipv4_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_neighbor_routes_cmd__X, &show_ip_bgp_neighbor_routes_cmd_bgpd, sizeof(show_ip_bgp_neighbor_routes_cmd_bgpd));
	memcpy(&__activeVars->aggregate_address_mask_as_set_cmd__X, &aggregate_address_mask_as_set_cmd_bgpd, sizeof(aggregate_address_mask_as_set_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_vpnv4_soft_in_cmd__X, &clear_ip_bgp_all_vpnv4_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_all_vpnv4_soft_in_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_community4_exact_cmd__X, &show_ip_bgp_ipv4_community4_exact_cmd_bgpd, sizeof(show_ip_bgp_ipv4_community4_exact_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_prefix_cmd__X, &show_ip_bgp_ipv4_prefix_cmd_bgpd, sizeof(show_ip_bgp_ipv4_prefix_cmd_bgpd));
	__activeVars->bgp_debug_option__X =  0;
	memcpy(&__activeVars->set_community_delete_cmd__X, &set_community_delete_cmd_bgpd, sizeof(set_community_delete_cmd_bgpd));
	memcpy(&__activeVars->neighbor_override_capability_cmd__X, &neighbor_override_capability_cmd_bgpd, sizeof(neighbor_override_capability_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_external_soft_out_cmd__X, &clear_ip_bgp_external_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_external_soft_out_cmd_bgpd));
	memcpy(&__activeVars->no_ip_as_path_cmd__X, &no_ip_as_path_cmd_bgpd, sizeof(no_ip_as_path_cmd_bgpd));
	memcpy(&__activeVars->neighbor_default_originate_cmd__X, &neighbor_default_originate_cmd_bgpd, sizeof(neighbor_default_originate_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_prefix_list_cmd__X, &show_ip_bgp_ipv4_prefix_list_cmd_bgpd, sizeof(show_ip_bgp_ipv4_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->route_match_metric_cmd__X, &route_match_metric_cmd_bgpd, sizeof(route_match_metric_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_capability_orf_prefix_cmd__X, &no_neighbor_capability_orf_prefix_cmd_bgpd, sizeof(no_neighbor_capability_orf_prefix_cmd_bgpd));
	__activeVars->retain_mode__X =  0;
	memcpy(&__activeVars->neighbor_maximum_prefix_threshold_restart_cmd__X, &neighbor_maximum_prefix_threshold_restart_cmd_bgpd, sizeof(neighbor_maximum_prefix_threshold_restart_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_community2_exact_cmd__X, &show_ip_bgp_ipv4_community2_exact_cmd_bgpd, sizeof(show_ip_bgp_ipv4_community2_exact_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_all_out_cmd__X, &clear_bgp_all_out_cmd_bgpd, sizeof(clear_bgp_all_out_cmd_bgpd));
	memcpy(&__activeVars->bgp_fast_external_failover_cmd__X, &bgp_fast_external_failover_cmd_bgpd, sizeof(bgp_fast_external_failover_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_group_ipv4_out_cmd__X, &clear_ip_bgp_peer_group_ipv4_out_cmd_bgpd, sizeof(clear_ip_bgp_peer_group_ipv4_out_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_peer_out_cmd__X, &clear_bgp_peer_out_cmd_bgpd, sizeof(clear_bgp_peer_out_cmd_bgpd));
	memcpy(&__activeVars->no_set_metric_val_cmd__X, &no_set_metric_val_cmd_bgpd, sizeof(no_set_metric_val_cmd_bgpd));
	memcpy(&__activeVars->neighbor_activate_cmd__X, &neighbor_activate_cmd_bgpd, sizeof(neighbor_activate_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_mask_route_map_cmd__X, &no_bgp_network_mask_route_map_cmd_bgpd, sizeof(no_bgp_network_mask_route_map_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_all_route_cmd__X, &show_ip_bgp_vpnv4_all_route_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_all_route_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_instance_all_soft_in_cmd__X, &clear_bgp_instance_all_soft_in_cmd_bgpd, sizeof(clear_bgp_instance_all_soft_in_cmd_bgpd));
	memcpy(&__activeVars->neighbor_description_cmd__X, &neighbor_description_cmd_bgpd, sizeof(neighbor_description_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_enforce_multihop_cmd__X, &no_neighbor_enforce_multihop_cmd_bgpd, sizeof(no_neighbor_enforce_multihop_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_external_ipv4_soft_in_cmd__X, &clear_ip_bgp_external_ipv4_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_external_ipv4_soft_in_cmd_bgpd));
	memcpy(&__activeVars->aggregate_address_mask_as_set_summary_cmd__X, &aggregate_address_mask_as_set_summary_cmd_bgpd, sizeof(aggregate_address_mask_as_set_summary_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_ipv6_route_map_cmd__X, &show_bgp_ipv6_route_map_cmd_bgpd, sizeof(show_bgp_ipv6_route_map_cmd_bgpd));
	memcpy(&__activeVars->no_set_local_pref_cmd__X, &no_set_local_pref_cmd_bgpd, sizeof(no_set_local_pref_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_client_to_client_reflection_cmd__X, &no_bgp_client_to_client_reflection_cmd_bgpd, sizeof(no_bgp_client_to_client_reflection_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_port_cmd__X, &no_neighbor_port_cmd_bgpd, sizeof(no_neighbor_port_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_route_reflector_client_cmd__X, &no_neighbor_route_reflector_client_cmd_bgpd, sizeof(no_neighbor_route_reflector_client_cmd_bgpd));
	memcpy(&__activeVars->no_set_community_delete_cmd__X, &no_set_community_delete_cmd_bgpd, sizeof(no_set_community_delete_cmd_bgpd));
	memcpy(&__activeVars->neighbor_remote_as_cmd__X, &neighbor_remote_as_cmd_bgpd, sizeof(neighbor_remote_as_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_fast_external_failover_cmd__X, &no_bgp_fast_external_failover_cmd_bgpd, sizeof(no_bgp_fast_external_failover_cmd_bgpd));
	__activeVars->orf_mode_str_max__X =  sizeof(orf_mode_str)/sizeof(orf_mode_str[0]);
	memcpy(&__activeVars->clear_ip_bgp_peer_group_out_cmd__X, &clear_ip_bgp_peer_group_out_cmd_bgpd, sizeof(clear_ip_bgp_peer_group_out_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_mask_natural_backdoor_ttl_cmd__X, &no_bgp_network_mask_natural_backdoor_ttl_cmd_bgpd, sizeof(no_bgp_network_mask_natural_backdoor_ttl_cmd_bgpd));
	memcpy(&__activeVars->no_match_pathlimit_as_val_cmd__X, &no_match_pathlimit_as_val_cmd_bgpd, sizeof(no_match_pathlimit_as_val_cmd_bgpd));
	memcpy(&__activeVars->no_match_ip_address_cmd__X, &no_match_ip_address_cmd_bgpd, sizeof(no_match_ip_address_cmd_bgpd));
	memcpy(&__activeVars->neighbor_route_server_client_cmd__X, &neighbor_route_server_client_cmd_bgpd, sizeof(neighbor_route_server_client_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_ipv4_soft_in_cmd__X, &clear_ip_bgp_as_ipv4_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_as_ipv4_soft_in_cmd_bgpd));
	__activeVars->bgp_scan_thread__X =  NULL;
	memcpy(&__activeVars->neighbor_filter_list_cmd__X, &neighbor_filter_list_cmd_bgpd, sizeof(neighbor_filter_list_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_attr_info_cmd__X, &show_ip_bgp_attr_info_cmd_bgpd, sizeof(show_ip_bgp_attr_info_cmd_bgpd));
	memcpy(&__activeVars->neighbor_strict_capability_cmd__X, &neighbor_strict_capability_cmd_bgpd, sizeof(neighbor_strict_capability_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_instance_ipv6_neighbors_peer_cmd__X, &show_bgp_instance_ipv6_neighbors_peer_cmd_bgpd, sizeof(show_bgp_instance_ipv6_neighbors_peer_cmd_bgpd));
	memcpy(&__activeVars->route_set_local_pref_cmd__X, &route_set_local_pref_cmd_bgpd, sizeof(route_set_local_pref_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_prefix_cmd__X, &show_ip_bgp_prefix_cmd_bgpd, sizeof(show_ip_bgp_prefix_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_neighbor_advertised_route_cmd__X, &show_ip_bgp_neighbor_advertised_route_cmd_bgpd, sizeof(show_ip_bgp_neighbor_advertised_route_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_as_in_prefix_filter_cmd__X, &clear_bgp_as_in_prefix_filter_cmd_bgpd, sizeof(clear_bgp_as_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_ipv6_neighbors_cmd__X, &show_bgp_ipv6_neighbors_cmd_bgpd, sizeof(show_bgp_ipv6_neighbors_cmd_bgpd));
	memcpy(&__activeVars->no_set_vpnv4_nexthop_cmd__X, &no_set_vpnv4_nexthop_cmd_bgpd, sizeof(no_set_vpnv4_nexthop_cmd_bgpd));
	memcpy(&__activeVars->no_match_community_exact_cmd__X, &no_match_community_exact_cmd_bgpd, sizeof(no_match_community_exact_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_instance_all_rsclient_cmd__X, &clear_ip_bgp_instance_all_rsclient_cmd_bgpd, sizeof(clear_ip_bgp_instance_all_rsclient_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_dampening_prefix_cmd__X, &clear_ip_bgp_dampening_prefix_cmd_bgpd, sizeof(clear_ip_bgp_dampening_prefix_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_cmd__X, &show_ip_bgp_ipv4_cmd_bgpd, sizeof(show_ip_bgp_ipv4_cmd_bgpd));
	memcpy(&__activeVars->ip_community_list_standard2_cmd__X, &ip_community_list_standard2_cmd_bgpd, sizeof(ip_community_list_standard2_cmd_bgpd));
	memcpy(&__activeVars->no_ip_extcommunity_list_name_standard_all_cmd__X, &no_ip_extcommunity_list_name_standard_all_cmd_bgpd, sizeof(no_ip_extcommunity_list_name_standard_all_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_instance_ipv4_summary_cmd__X, &show_ip_bgp_instance_ipv4_summary_cmd_bgpd, sizeof(show_ip_bgp_instance_ipv4_summary_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_mask_natural_route_map_cmd__X, &no_bgp_network_mask_natural_route_map_cmd_bgpd, sizeof(no_bgp_network_mask_natural_route_map_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_prefix_list_cmd__X, &show_ip_bgp_prefix_list_cmd_bgpd, sizeof(show_ip_bgp_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_redistribute_ipv4_metric_cmd__X, &no_bgp_redistribute_ipv4_metric_cmd_bgpd, sizeof(no_bgp_redistribute_ipv4_metric_cmd_bgpd));
	memcpy(&__activeVars->route_match_ip_next_hop_prefix_list_cmd__X, &route_match_ip_next_hop_prefix_list_cmd_bgpd, sizeof(route_match_ip_next_hop_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_password_cmd__X, &no_neighbor_password_cmd_bgpd, sizeof(no_neighbor_password_cmd_bgpd));
	__activeVars->damp__X =  &bgp_damp_cfg;
	memcpy(&__activeVars->debug_bgp_fsm_cmd__X, &debug_bgp_fsm_cmd_bgpd, sizeof(debug_bgp_fsm_cmd_bgpd));
	memcpy(&__activeVars->no_aggregate_address_mask_as_set_summary_cmd__X, &no_aggregate_address_mask_as_set_summary_cmd_bgpd, sizeof(no_aggregate_address_mask_as_set_summary_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_community2_cmd__X, &show_ip_bgp_community2_cmd_bgpd, sizeof(show_ip_bgp_community2_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_rd_cmd__X, &show_ip_bgp_vpnv4_rd_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_rd_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_community_exact_cmd__X, &show_ip_bgp_community_exact_cmd_bgpd, sizeof(show_ip_bgp_community_exact_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_instance_neighbors_cmd__X, &show_bgp_instance_neighbors_cmd_bgpd, sizeof(show_bgp_instance_neighbors_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_instance_neighbors_peer_cmd__X, &show_bgp_instance_neighbors_peer_cmd_bgpd, sizeof(show_bgp_instance_neighbors_peer_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_soft_cmd__X, &clear_bgp_ipv6_peer_soft_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_soft_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_advertise_interval_cmd__X, &no_neighbor_advertise_interval_cmd_bgpd, sizeof(no_neighbor_advertise_interval_cmd_bgpd));
	memcpy(&__activeVars->neighbor_soft_reconfiguration_cmd__X, &neighbor_soft_reconfiguration_cmd_bgpd, sizeof(neighbor_soft_reconfiguration_cmd_bgpd));
	memcpy(&__activeVars->no_match_origin_cmd__X, &no_match_origin_cmd_bgpd, sizeof(no_match_origin_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_soft_out_cmd__X, &clear_ip_bgp_all_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_all_soft_out_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_scan_time_cmd__X, &no_bgp_scan_time_cmd_bgpd, sizeof(no_bgp_scan_time_cmd_bgpd));
	memcpy(&__activeVars->aggregate_address_cmd__X, &aggregate_address_cmd_bgpd, sizeof(aggregate_address_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_description_cmd__X, &no_neighbor_description_cmd_bgpd, sizeof(no_neighbor_description_cmd_bgpd));
	memcpy(&__activeVars->undebug_bgp_normal_cmd__X, &undebug_bgp_normal_cmd_bgpd, sizeof(undebug_bgp_normal_cmd_bgpd));
	memcpy(&__activeVars->aggregate_address_mask_cmd__X, &aggregate_address_mask_cmd_bgpd, sizeof(aggregate_address_mask_cmd_bgpd));
	memcpy(&__activeVars->ip_community_list_expanded_cmd__X, &ip_community_list_expanded_cmd_bgpd, sizeof(ip_community_list_expanded_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_external_soft_out_cmd__X, &clear_bgp_external_soft_out_cmd_bgpd, sizeof(clear_bgp_external_soft_out_cmd_bgpd));
	memcpy(&__activeVars->no_match_pathlimit_as_cmd__X, &no_match_pathlimit_as_cmd_bgpd, sizeof(no_match_pathlimit_as_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_bestpath_aspath_confed_cmd__X, &no_bgp_bestpath_aspath_confed_cmd_bgpd, sizeof(no_bgp_bestpath_aspath_confed_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_cmd__X, &no_bgp_network_cmd_bgpd, sizeof(no_bgp_network_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_flap_route_map_cmd__X, &show_ip_bgp_flap_route_map_cmd_bgpd, sizeof(show_ip_bgp_flap_route_map_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_maximum_prefix_warning_cmd__X, &no_neighbor_maximum_prefix_warning_cmd_bgpd, sizeof(no_neighbor_maximum_prefix_warning_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_external_out_cmd__X, &clear_ip_bgp_external_out_cmd_bgpd, sizeof(clear_ip_bgp_external_out_cmd_bgpd));
	memcpy(&__activeVars->bgp_multiple_instance_cmd__X, &bgp_multiple_instance_cmd_bgpd, sizeof(bgp_multiple_instance_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_log_neighbor_changes_cmd__X, &no_bgp_log_neighbor_changes_cmd_bgpd, sizeof(no_bgp_log_neighbor_changes_cmd_bgpd));
	memcpy(&__activeVars->match_ip_next_hop_prefix_list_cmd__X, &match_ip_next_hop_prefix_list_cmd_bgpd, sizeof(match_ip_next_hop_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_peer_in_cmd__X, &clear_bgp_peer_in_cmd_bgpd, sizeof(clear_bgp_peer_in_cmd_bgpd));
	memcpy(&__activeVars->neighbor_attr_unchanged4_cmd__X, &neighbor_attr_unchanged4_cmd_bgpd, sizeof(neighbor_attr_unchanged4_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_in_cmd__X, &clear_ip_bgp_all_in_cmd_bgpd, sizeof(clear_ip_bgp_all_in_cmd_bgpd));
	memcpy(&__activeVars->neighbor_default_originate_rmap_cmd__X, &neighbor_default_originate_rmap_cmd_bgpd, sizeof(neighbor_default_originate_rmap_cmd_bgpd));
	memcpy(&__activeVars->match_ip_address_prefix_list_cmd__X, &match_ip_address_prefix_list_cmd_bgpd, sizeof(match_ip_address_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->no_set_aspath_exclude_val_cmd__X, &no_set_aspath_exclude_val_cmd_bgpd, sizeof(no_set_aspath_exclude_val_cmd_bgpd));
	memcpy(&__activeVars->no_set_ip_nexthop_peer_cmd__X, &no_set_ip_nexthop_peer_cmd_bgpd, sizeof(no_set_ip_nexthop_peer_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_all_cmd__X, &show_ip_bgp_vpnv4_all_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_all_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_prefix_longer_cmd__X, &show_ip_bgp_prefix_longer_cmd_bgpd, sizeof(show_ip_bgp_prefix_longer_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_instance_all_soft_out_cmd__X, &clear_bgp_instance_all_soft_out_cmd_bgpd, sizeof(clear_bgp_instance_all_soft_out_cmd_bgpd));
	memcpy(&__activeVars->exit_address_family_cmd__X, &exit_address_family_cmd_bgpd, sizeof(exit_address_family_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_attr_unchanged2_cmd__X, &no_neighbor_attr_unchanged2_cmd_bgpd, sizeof(no_neighbor_attr_unchanged2_cmd_bgpd));
	memcpy(&__activeVars->no_match_metric_cmd__X, &no_match_metric_cmd_bgpd, sizeof(no_match_metric_cmd_bgpd));
	memcpy(&__activeVars->bgp_bestpath_med3_cmd__X, &bgp_bestpath_med3_cmd_bgpd, sizeof(bgp_bestpath_med3_cmd_bgpd));
	memcpy(&__activeVars->set_ip_nexthop_cmd__X, &set_ip_nexthop_cmd_bgpd, sizeof(set_ip_nexthop_cmd_bgpd));
	memcpy(&__activeVars->bgp_client_to_client_reflection_cmd__X, &bgp_client_to_client_reflection_cmd_bgpd, sizeof(bgp_client_to_client_reflection_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_ttl_cmd__X, &bgp_network_ttl_cmd_bgpd, sizeof(bgp_network_ttl_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_dampening_address_mask_cmd__X, &clear_ip_bgp_dampening_address_mask_cmd_bgpd, sizeof(clear_ip_bgp_dampening_address_mask_cmd_bgpd));
	memcpy(&__activeVars->dump_bgp_updates_interval_cmd__X, &dump_bgp_updates_interval_cmd_bgpd, sizeof(dump_bgp_updates_interval_cmd_bgpd));
	memcpy(&__activeVars->no_ip_community_list_standard_all_cmd__X, &no_ip_community_list_standard_all_cmd_bgpd, sizeof(no_ip_community_list_standard_all_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_redistribute_ipv4_rmap_metric_cmd__X, &no_bgp_redistribute_ipv4_rmap_metric_cmd_bgpd, sizeof(no_bgp_redistribute_ipv4_rmap_metric_cmd_bgpd));
	__activeVars->bgp_notify_open_msg_max__X =  BGP_NOTIFY_OPEN_MAX;
	memcpy(&__activeVars->no_ip_extcommunity_list_expanded_all_cmd__X, &no_ip_extcommunity_list_expanded_all_cmd_bgpd, sizeof(no_ip_extcommunity_list_expanded_all_cmd_bgpd));
	memcpy(&__activeVars->set_atomic_aggregate_cmd__X, &set_atomic_aggregate_cmd_bgpd, sizeof(set_atomic_aggregate_cmd_bgpd));
	memcpy(&__activeVars->no_match_ip_next_hop_val_cmd__X, &no_match_ip_next_hop_val_cmd_bgpd, sizeof(no_match_ip_next_hop_val_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_all_neighbor_advertised_routes_cmd__X, &show_ip_bgp_vpnv4_all_neighbor_advertised_routes_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_all_neighbor_advertised_routes_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_soft_reconfiguration_cmd__X, &no_neighbor_soft_reconfiguration_cmd_bgpd, sizeof(no_neighbor_soft_reconfiguration_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_distance_cmd__X, &no_bgp_distance_cmd_bgpd, sizeof(no_bgp_distance_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_default_local_preference_cmd__X, &no_bgp_default_local_preference_cmd_bgpd, sizeof(no_bgp_default_local_preference_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_bestpath_compare_router_id_cmd__X, &no_bgp_bestpath_compare_router_id_cmd_bgpd, sizeof(no_bgp_bestpath_compare_router_id_cmd_bgpd));
	memcpy(&__activeVars->match_community_cmd__X, &match_community_cmd_bgpd, sizeof(match_community_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_maximum_prefix_restart_cmd__X, &no_neighbor_maximum_prefix_restart_cmd_bgpd, sizeof(no_neighbor_maximum_prefix_restart_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_rd_tags_cmd__X, &show_ip_bgp_vpnv4_rd_tags_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_rd_tags_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_neighbors_cmd__X, &show_bgp_neighbors_cmd_bgpd, sizeof(show_bgp_neighbors_cmd_bgpd));
	memcpy(&__activeVars->no_set_originator_id_cmd__X, &no_set_originator_id_cmd_bgpd, sizeof(no_set_originator_id_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_all_prefix_cmd__X, &show_ip_bgp_vpnv4_all_prefix_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_all_prefix_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_maximum_prefix_threshold_warning_cmd__X, &no_neighbor_maximum_prefix_threshold_warning_cmd_bgpd, sizeof(no_neighbor_maximum_prefix_threshold_warning_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_rsclient_prefix_cmd__X, &show_ip_bgp_rsclient_prefix_cmd_bgpd, sizeof(show_ip_bgp_rsclient_prefix_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_mask_natural_backdoor_cmd__X, &no_bgp_network_mask_natural_backdoor_cmd_bgpd, sizeof(no_bgp_network_mask_natural_backdoor_cmd_bgpd));
	memcpy(&__activeVars->route_match_aspath_cmd__X, &route_match_aspath_cmd_bgpd, sizeof(route_match_aspath_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_cmd__X, &clear_ip_bgp_peer_cmd_bgpd, sizeof(clear_ip_bgp_peer_cmd_bgpd));
	memcpy(&__activeVars->route_set_originator_id_cmd__X, &route_set_originator_id_cmd_bgpd, sizeof(route_set_originator_id_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_distance2_cmd__X, &no_bgp_distance2_cmd_bgpd, sizeof(no_bgp_distance2_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_instance_all_in_prefix_filter_cmd__X, &clear_ip_bgp_instance_all_in_prefix_filter_cmd_bgpd, sizeof(clear_ip_bgp_instance_all_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_ipv4_soft_out_cmd__X, &clear_ip_bgp_as_ipv4_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_as_ipv4_soft_out_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_maximum_prefix_val_cmd__X, &no_neighbor_maximum_prefix_val_cmd_bgpd, sizeof(no_neighbor_maximum_prefix_val_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_group_in_prefix_filter_cmd__X, &clear_bgp_ipv6_peer_group_in_prefix_filter_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_group_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->community_list_node__X, &community_list_node__T, sizeof(community_list_node__T));
	memcpy(&__activeVars->aggregate_address_as_set_summary_cmd__X, &aggregate_address_as_set_summary_cmd_bgpd, sizeof(aggregate_address_as_set_summary_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_mask_backdoor_cmd__X, &no_bgp_network_mask_backdoor_cmd_bgpd, sizeof(no_bgp_network_mask_backdoor_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_ipv4_soft_cmd__X, &clear_ip_bgp_all_ipv4_soft_cmd_bgpd, sizeof(clear_ip_bgp_all_ipv4_soft_cmd_bgpd));
	memcpy(&__activeVars->no_router_bgp_view_cmd__X, &no_router_bgp_view_cmd_bgpd, sizeof(no_router_bgp_view_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_send_community_type_cmd__X, &no_neighbor_send_community_type_cmd_bgpd, sizeof(no_neighbor_send_community_type_cmd_bgpd));
	memcpy(&__activeVars->no_ip_extcommunity_list_name_expanded_cmd__X, &no_ip_extcommunity_list_name_expanded_cmd_bgpd, sizeof(no_ip_extcommunity_list_name_expanded_cmd_bgpd));
	memcpy(&__activeVars->no_ip_community_list_name_expanded_cmd__X, &no_ip_community_list_name_expanded_cmd_bgpd, sizeof(no_ip_community_list_name_expanded_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_bestpath_aspath_ignore_cmd__X, &no_bgp_bestpath_aspath_ignore_cmd_bgpd, sizeof(no_bgp_bestpath_aspath_ignore_cmd_bgpd));
	__activeVars->zlookup__X =  NULL;
	__activeVars->vty_port__X =  BGP_VTY_PORT;
	memcpy(&__activeVars->no_bgp_graceful_restart_stalepath_time_val_cmd__X, &no_bgp_graceful_restart_stalepath_time_val_cmd_bgpd, sizeof(no_bgp_graceful_restart_stalepath_time_val_cmd_bgpd));
	memcpy(&__activeVars->undebug_bgp_update_cmd__X, &undebug_bgp_update_cmd_bgpd, sizeof(undebug_bgp_update_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_group_ipv4_soft_in_cmd__X, &clear_ip_bgp_peer_group_ipv4_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_peer_group_ipv4_soft_in_cmd_bgpd));
	memcpy(&__activeVars->no_set_vpnv4_nexthop_val_cmd__X, &no_set_vpnv4_nexthop_val_cmd_bgpd, sizeof(no_set_vpnv4_nexthop_val_cmd_bgpd));
	memcpy(&__activeVars->show_ip_community_list_cmd__X, &show_ip_community_list_cmd_bgpd, sizeof(show_ip_community_list_cmd_bgpd));
	memcpy(&__activeVars->bgp_default_ipv4_unicast_cmd__X, &bgp_default_ipv4_unicast_cmd_bgpd, sizeof(bgp_default_ipv4_unicast_cmd_bgpd));
	memcpy(&__activeVars->set_weight_cmd__X, &set_weight_cmd_bgpd, sizeof(set_weight_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_redistribute_ipv4_rmap_cmd__X, &no_bgp_redistribute_ipv4_rmap_cmd_bgpd, sizeof(no_bgp_redistribute_ipv4_rmap_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_rd_prefix_cmd__X, &show_ip_bgp_vpnv4_rd_prefix_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_rd_prefix_cmd_bgpd));
	memcpy(&__activeVars->neighbor_version_cmd__X, &neighbor_version_cmd_bgpd, sizeof(neighbor_version_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_external_in_prefix_filter_cmd__X, &clear_bgp_ipv6_external_in_prefix_filter_cmd_bgpd, sizeof(clear_bgp_ipv6_external_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_vpnv4_soft_out_cmd__X, &clear_ip_bgp_peer_vpnv4_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_peer_vpnv4_soft_out_cmd_bgpd));
	memcpy(&__activeVars->no_ip_community_list_name_standard_all_cmd__X, &no_ip_community_list_name_standard_all_cmd_bgpd, sizeof(no_ip_community_list_name_standard_all_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_attr_unchanged6_cmd__X, &no_neighbor_attr_unchanged6_cmd_bgpd, sizeof(no_neighbor_attr_unchanged6_cmd_bgpd));
	memcpy(&__activeVars->neighbor_transparent_nexthop_cmd__X, &neighbor_transparent_nexthop_cmd_bgpd, sizeof(neighbor_transparent_nexthop_cmd_bgpd));
	memcpy(&__activeVars->no_match_ip_next_hop_cmd__X, &no_match_ip_next_hop_cmd_bgpd, sizeof(no_match_ip_next_hop_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_external_in_cmd__X, &clear_ip_bgp_external_in_cmd_bgpd, sizeof(clear_ip_bgp_external_in_cmd_bgpd));
	memcpy(&__activeVars->undebug_bgp_filter_cmd__X, &undebug_bgp_filter_cmd_bgpd, sizeof(undebug_bgp_filter_cmd_bgpd));
	memcpy(&__activeVars->route_set_weight_cmd__X, &route_set_weight_cmd_bgpd, sizeof(route_set_weight_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_instance_peer_rsclient_cmd__X, &clear_ip_bgp_instance_peer_rsclient_cmd_bgpd, sizeof(clear_ip_bgp_instance_peer_rsclient_cmd_bgpd));
	memcpy(&__activeVars->neighbor_unsuppress_map_cmd__X, &neighbor_unsuppress_map_cmd_bgpd, sizeof(neighbor_unsuppress_map_cmd_bgpd));
	memcpy(&__activeVars->no_dump_bgp_updates_cmd__X, &no_dump_bgp_updates_cmd_bgpd, sizeof(no_dump_bgp_updates_cmd_bgpd));
	memcpy(&__activeVars->as_list_master__X, &as_list_master__T, sizeof(as_list_master__T));
	memcpy(&__activeVars->no_neighbor_local_as_val2_cmd__X, &no_neighbor_local_as_val2_cmd_bgpd, sizeof(no_neighbor_local_as_val2_cmd_bgpd));
	memcpy(&__activeVars->no_match_ip_next_hop_prefix_list_cmd__X, &no_match_ip_next_hop_prefix_list_cmd_bgpd, sizeof(no_match_ip_next_hop_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->no_dump_bgp_all_cmd__X, &no_dump_bgp_all_cmd_bgpd, sizeof(no_dump_bgp_all_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_neighbor_advertised_route_cmd__X, &show_ip_bgp_ipv4_neighbor_advertised_route_cmd_bgpd, sizeof(show_ip_bgp_ipv4_neighbor_advertised_route_cmd_bgpd));
	memcpy(&__activeVars->no_set_local_pref_val_cmd__X, &no_set_local_pref_val_cmd_bgpd, sizeof(no_set_local_pref_val_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_backdoor_ttl_cmd__X, &no_bgp_network_backdoor_ttl_cmd_bgpd, sizeof(no_bgp_network_backdoor_ttl_cmd_bgpd));
	memcpy(&__activeVars->neighbor_advertise_interval_cmd__X, &neighbor_advertise_interval_cmd_bgpd, sizeof(neighbor_advertise_interval_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_in_prefix_filter_cmd__X, &clear_ip_bgp_all_in_prefix_filter_cmd_bgpd, sizeof(clear_ip_bgp_all_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->neighbor_attr_unchanged1_cmd__X, &neighbor_attr_unchanged1_cmd_bgpd, sizeof(neighbor_attr_unchanged1_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_view_rsclient_cmd__X, &show_ip_bgp_view_rsclient_cmd_bgpd, sizeof(show_ip_bgp_view_rsclient_cmd_bgpd));
	memcpy(&__activeVars->neighbor_dont_capability_negotiate_cmd__X, &neighbor_dont_capability_negotiate_cmd_bgpd, sizeof(neighbor_dont_capability_negotiate_cmd_bgpd));
	memcpy(&__activeVars->vpnv4_network_cmd__X, &vpnv4_network_cmd_bgpd, sizeof(vpnv4_network_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_group_soft_cmd__X, &clear_bgp_ipv6_peer_group_soft_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_group_soft_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_default_ipv4_unicast_cmd__X, &no_bgp_default_ipv4_unicast_cmd_bgpd, sizeof(no_bgp_default_ipv4_unicast_cmd_bgpd));
	memcpy(&__activeVars->dump_bgp_all_interval_cmd__X, &dump_bgp_all_interval_cmd_bgpd, sizeof(dump_bgp_all_interval_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_peer_group_in_cmd__X, &clear_bgp_peer_group_in_cmd_bgpd, sizeof(clear_bgp_peer_group_in_cmd_bgpd));
	memcpy(&__activeVars->match_peer_local_cmd__X, &match_peer_local_cmd_bgpd, sizeof(match_peer_local_cmd_bgpd));
	memcpy(&__activeVars->no_ip_extcommunity_list_expanded_cmd__X, &no_ip_extcommunity_list_expanded_cmd_bgpd, sizeof(no_ip_extcommunity_list_expanded_cmd_bgpd));
	memcpy(&__activeVars->bgp_log_neighbor_changes_cmd__X, &bgp_log_neighbor_changes_cmd_bgpd, sizeof(bgp_log_neighbor_changes_cmd_bgpd));
	memcpy(&__activeVars->bgp_enforce_first_as_cmd__X, &bgp_enforce_first_as_cmd_bgpd, sizeof(bgp_enforce_first_as_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_activate_cmd__X, &no_neighbor_activate_cmd_bgpd, sizeof(no_neighbor_activate_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_group_ipv4_in_prefix_filter_cmd__X, &clear_ip_bgp_peer_group_ipv4_in_prefix_filter_cmd_bgpd, sizeof(clear_ip_bgp_peer_group_ipv4_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_as_in_cmd__X, &clear_bgp_ipv6_as_in_cmd_bgpd, sizeof(clear_bgp_ipv6_as_in_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_route_map_cmd__X, &show_ip_bgp_ipv4_route_map_cmd_bgpd, sizeof(show_ip_bgp_ipv4_route_map_cmd_bgpd));
	memcpy(&__activeVars->no_set_community_cmd__X, &no_set_community_cmd_bgpd, sizeof(no_set_community_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_passive_cmd__X, &no_neighbor_passive_cmd_bgpd, sizeof(no_neighbor_passive_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_maximum_prefix_threshold_cmd__X, &no_neighbor_maximum_prefix_threshold_cmd_bgpd, sizeof(no_neighbor_maximum_prefix_threshold_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_peer_group_cmd__X, &no_neighbor_peer_group_cmd_bgpd, sizeof(no_neighbor_peer_group_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_vpnv4_out_cmd__X, &clear_ip_bgp_peer_vpnv4_out_cmd_bgpd, sizeof(clear_ip_bgp_peer_vpnv4_out_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_soft_out_cmd__X, &clear_bgp_ipv6_peer_soft_out_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_soft_out_cmd_bgpd));
	memcpy(&__activeVars->address_family_ipv6_cmd__X, &address_family_ipv6_cmd_bgpd, sizeof(address_family_ipv6_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_redistribute_ipv4_cmd__X, &no_bgp_redistribute_ipv4_cmd_bgpd, sizeof(no_bgp_redistribute_ipv4_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_timers_arg_cmd__X, &no_bgp_timers_arg_cmd_bgpd, sizeof(no_bgp_timers_arg_cmd_bgpd));
	memcpy(&__activeVars->no_match_peer_local_cmd__X, &no_match_peer_local_cmd_bgpd, sizeof(no_match_peer_local_cmd_bgpd));
	memcpy(&__activeVars->no_set_ip_nexthop_val_cmd__X, &no_set_ip_nexthop_val_cmd_bgpd, sizeof(no_set_ip_nexthop_val_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_mask_natural_ttl_cmd__X, &no_bgp_network_mask_natural_ttl_cmd_bgpd, sizeof(no_bgp_network_mask_natural_ttl_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_as_soft_in_cmd__X, &clear_bgp_ipv6_as_soft_in_cmd_bgpd, sizeof(clear_bgp_ipv6_as_soft_in_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_import_check_cmd__X, &no_bgp_network_import_check_cmd_bgpd, sizeof(no_bgp_network_import_check_cmd_bgpd));
	memcpy(&__activeVars->no_ip_community_list_standard_cmd__X, &no_ip_community_list_standard_cmd_bgpd, sizeof(no_ip_community_list_standard_cmd_bgpd));
	memcpy(&__activeVars->address_family_ipv6_safi_cmd__X, &address_family_ipv6_safi_cmd_bgpd, sizeof(address_family_ipv6_safi_cmd_bgpd));
	memcpy(&__activeVars->no_match_ip_route_source_prefix_list_val_cmd__X, &no_match_ip_route_source_prefix_list_val_cmd_bgpd, sizeof(no_match_ip_route_source_prefix_list_val_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_mask_cmd__X, &bgp_network_mask_cmd_bgpd, sizeof(bgp_network_mask_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_community4_cmd__X, &show_ip_bgp_community4_cmd_bgpd, sizeof(show_ip_bgp_community4_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_rsclient_cmd__X, &clear_ip_bgp_all_rsclient_cmd_bgpd, sizeof(clear_ip_bgp_all_rsclient_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_backdoor_cmd__X, &bgp_network_backdoor_cmd_bgpd, sizeof(bgp_network_backdoor_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_instance_all_cmd__X, &clear_ip_bgp_instance_all_cmd_bgpd, sizeof(clear_ip_bgp_instance_all_cmd_bgpd));
	memcpy(&__activeVars->no_match_ecommunity_val_cmd__X, &no_match_ecommunity_val_cmd_bgpd, sizeof(no_match_ecommunity_val_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_flap_prefix_longer_cmd__X, &show_ip_bgp_flap_prefix_longer_cmd_bgpd, sizeof(show_ip_bgp_flap_prefix_longer_cmd_bgpd));
	memcpy(&__activeVars->no_set_weight_cmd__X, &no_set_weight_cmd_bgpd, sizeof(no_set_weight_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_views_cmd__X, &show_bgp_views_cmd_bgpd, sizeof(show_bgp_views_cmd_bgpd));
	memcpy(&__activeVars->neighbor_distribute_list_cmd__X, &neighbor_distribute_list_cmd_bgpd, sizeof(neighbor_distribute_list_cmd_bgpd));
	memcpy(&__activeVars->ip_as_path_cmd__X, &ip_as_path_cmd_bgpd, sizeof(ip_as_path_cmd_bgpd));
	memcpy(&__activeVars->no_match_community_cmd__X, &no_match_community_cmd_bgpd, sizeof(no_match_community_cmd_bgpd));
	memcpy(&__activeVars->set_ip_nexthop_peer_cmd__X, &set_ip_nexthop_peer_cmd_bgpd, sizeof(set_ip_nexthop_peer_cmd_bgpd));
	memcpy(&__activeVars->neighbor_timers_cmd__X, &neighbor_timers_cmd_bgpd, sizeof(neighbor_timers_cmd_bgpd));
	memcpy(&__activeVars->no_set_aggregator_as_cmd__X, &no_set_aggregator_as_cmd_bgpd, sizeof(no_set_aggregator_as_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_bestpath_med_cmd__X, &no_bgp_bestpath_med_cmd_bgpd, sizeof(no_bgp_bestpath_med_cmd_bgpd));
	memcpy(&__activeVars->route_match_ip_next_hop_cmd__X, &route_match_ip_next_hop_cmd_bgpd, sizeof(route_match_ip_next_hop_cmd_bgpd));
	memcpy(&__activeVars->bgp_damp_set2_cmd__X, &bgp_damp_set2_cmd_bgpd, sizeof(bgp_damp_set2_cmd_bgpd));
	__activeVars->pid_file__X =  PATH_BGPD_PID;
	memcpy(&__activeVars->show_ip_bgp_flap_statistics_cmd__X, &show_ip_bgp_flap_statistics_cmd_bgpd, sizeof(show_ip_bgp_flap_statistics_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_vpnv4_soft_cmd__X, &clear_ip_bgp_peer_vpnv4_soft_cmd_bgpd, sizeof(clear_ip_bgp_peer_vpnv4_soft_cmd_bgpd));
	memcpy(&__activeVars->route_set_aggregator_as_cmd__X, &route_set_aggregator_as_cmd_bgpd, sizeof(route_set_aggregator_as_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_all_in_prefix_filter_cmd__X, &clear_bgp_ipv6_all_in_prefix_filter_cmd_bgpd, sizeof(clear_bgp_ipv6_all_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->debug_bgp_normal_cmd__X, &debug_bgp_normal_cmd_bgpd, sizeof(debug_bgp_normal_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_mask_ttl_cmd__X, &no_bgp_network_mask_ttl_cmd_bgpd, sizeof(no_bgp_network_mask_ttl_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_external_out_cmd__X, &clear_bgp_ipv6_external_out_cmd_bgpd, sizeof(clear_bgp_ipv6_external_out_cmd_bgpd));
	memcpy(&__activeVars->debug_bgp_zebra_cmd__X, &debug_bgp_zebra_cmd_bgpd, sizeof(debug_bgp_zebra_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_weight_val_cmd__X, &no_neighbor_weight_val_cmd_bgpd, sizeof(no_neighbor_weight_val_cmd_bgpd));
	memcpy(&__activeVars->route_set_aspath_exclude_cmd__X, &route_set_aspath_exclude_cmd_bgpd, sizeof(route_set_aspath_exclude_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_paths_cmd__X, &show_ip_bgp_ipv4_paths_cmd_bgpd, sizeof(show_ip_bgp_ipv4_paths_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_distance_source_cmd__X, &no_bgp_distance_source_cmd_bgpd, sizeof(no_bgp_distance_source_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_out_cmd__X, &clear_ip_bgp_peer_out_cmd_bgpd, sizeof(clear_ip_bgp_peer_out_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_memory_cmd__X, &show_bgp_memory_cmd_bgpd, sizeof(show_bgp_memory_cmd_bgpd));
	memcpy(&__activeVars->neighbor_set_peer_group_cmd__X, &neighbor_set_peer_group_cmd_bgpd, sizeof(neighbor_set_peer_group_cmd_bgpd));
	memcpy(&__activeVars->debug_bgp_update_cmd__X, &debug_bgp_update_cmd_bgpd, sizeof(debug_bgp_update_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_ipv4_out_cmd__X, &clear_ip_bgp_peer_ipv4_out_cmd_bgpd, sizeof(clear_ip_bgp_peer_ipv4_out_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_peer_cmd__X, &clear_bgp_peer_cmd_bgpd, sizeof(clear_bgp_peer_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_soft_out_cmd__X, &clear_ip_bgp_peer_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_peer_soft_out_cmd_bgpd));
	__activeVars->bgp_import_thread__X =  NULL;
	memcpy(&__activeVars->show_ip_bgp_ipv4_regexp_cmd__X, &show_ip_bgp_ipv4_regexp_cmd_bgpd, sizeof(show_ip_bgp_ipv4_regexp_cmd_bgpd));
	memcpy(&__activeVars->match_ecommunity_cmd__X, &match_ecommunity_cmd_bgpd, sizeof(match_ecommunity_cmd_bgpd));
	memcpy(&__activeVars->no_ip_community_list_name_standard_cmd__X, &no_ip_community_list_name_standard_cmd_bgpd, sizeof(no_ip_community_list_name_standard_cmd_bgpd));
	memcpy(&__activeVars->no_match_ip_address_prefix_list_val_cmd__X, &no_match_ip_address_prefix_list_val_cmd_bgpd, sizeof(no_match_ip_address_prefix_list_val_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_instance_summary_cmd__X, &show_ip_bgp_instance_summary_cmd_bgpd, sizeof(show_ip_bgp_instance_summary_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_as_soft_out_cmd__X, &clear_bgp_as_soft_out_cmd_bgpd, sizeof(clear_bgp_as_soft_out_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_peer_group_soft_cmd__X, &clear_bgp_peer_group_soft_cmd_bgpd, sizeof(clear_bgp_peer_group_soft_cmd_bgpd));
	memcpy(&__activeVars->set_metric_cmd__X, &set_metric_cmd_bgpd, sizeof(set_metric_cmd_bgpd));
	memcpy(&__activeVars->bgp_timers_cmd__X, &bgp_timers_cmd_bgpd, sizeof(bgp_timers_cmd_bgpd));
	memcpy(&__activeVars->neighbor_interface_cmd__X, &neighbor_interface_cmd_bgpd, sizeof(neighbor_interface_cmd_bgpd));
	memcpy(&__activeVars->neighbor_send_community_type_cmd__X, &neighbor_send_community_type_cmd_bgpd, sizeof(neighbor_send_community_type_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_neighbor_flap_cmd__X, &show_ip_bgp_neighbor_flap_cmd_bgpd, sizeof(show_ip_bgp_neighbor_flap_cmd_bgpd));
	memcpy(&__activeVars->no_ip_as_path_all_cmd__X, &no_ip_as_path_all_cmd_bgpd, sizeof(no_ip_as_path_all_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_send_community_cmd__X, &no_neighbor_send_community_cmd_bgpd, sizeof(no_neighbor_send_community_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_strict_capability_cmd__X, &no_neighbor_strict_capability_cmd_bgpd, sizeof(no_neighbor_strict_capability_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_update_source_cmd__X, &no_neighbor_update_source_cmd_bgpd, sizeof(no_neighbor_update_source_cmd_bgpd));
	memcpy(&__activeVars->match_origin_cmd__X, &match_origin_cmd_bgpd, sizeof(match_origin_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_timers_connect_cmd__X, &no_neighbor_timers_connect_cmd_bgpd, sizeof(no_neighbor_timers_connect_cmd_bgpd));
	memcpy(&__activeVars->set_aspath_prepend_cmd__X, &set_aspath_prepend_cmd_bgpd, sizeof(set_aspath_prepend_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_external_ipv4_in_cmd__X, &clear_ip_bgp_external_ipv4_in_cmd_bgpd, sizeof(clear_ip_bgp_external_ipv4_in_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_regexp_cmd__X, &show_ip_bgp_regexp_cmd_bgpd, sizeof(show_ip_bgp_regexp_cmd_bgpd));
	memcpy(&__activeVars->ip_community_list_name_standard_cmd__X, &ip_community_list_name_standard_cmd_bgpd, sizeof(ip_community_list_name_standard_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_as_out_cmd__X, &clear_bgp_as_out_cmd_bgpd, sizeof(clear_bgp_as_out_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_weight_cmd__X, &no_neighbor_weight_cmd_bgpd, sizeof(no_neighbor_weight_cmd_bgpd));
	memcpy(&__activeVars->bgp_redistribute_ipv4_rmap_cmd__X, &bgp_redistribute_ipv4_rmap_cmd_bgpd, sizeof(bgp_redistribute_ipv4_rmap_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_group_ipv4_in_cmd__X, &clear_ip_bgp_peer_group_ipv4_in_cmd_bgpd, sizeof(clear_ip_bgp_peer_group_ipv4_in_cmd_bgpd));
	memcpy(&__activeVars->dump_bgp_routes_interval_cmd__X, &dump_bgp_routes_interval_cmd_bgpd, sizeof(dump_bgp_routes_interval_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_dampened_paths_cmd__X, &show_ip_bgp_dampened_paths_cmd_bgpd, sizeof(show_ip_bgp_dampened_paths_cmd_bgpd));
	memcpy(&__activeVars->no_aggregate_address_as_set_summary_cmd__X, &no_aggregate_address_as_set_summary_cmd_bgpd, sizeof(no_aggregate_address_as_set_summary_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_group_in_cmd__X, &clear_ip_bgp_peer_group_in_cmd_bgpd, sizeof(clear_ip_bgp_peer_group_in_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_external_in_cmd__X, &clear_bgp_ipv6_external_in_cmd_bgpd, sizeof(clear_bgp_ipv6_external_in_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_neighbor_routes_cmd__X, &show_ip_bgp_ipv4_neighbor_routes_cmd_bgpd, sizeof(show_ip_bgp_ipv4_neighbor_routes_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_cmd__X, &clear_bgp_ipv6_peer_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_cmd_bgpd));
	__activeVars->attr_str_max__X =  sizeof(attr_str)/sizeof(attr_str[0]);
	memcpy(&__activeVars->no_neighbor_nexthop_self_cmd__X, &no_neighbor_nexthop_self_cmd_bgpd, sizeof(no_neighbor_nexthop_self_cmd_bgpd));
	memcpy(&__activeVars->debug_bgp_as4_segment_cmd__X, &debug_bgp_as4_segment_cmd_bgpd, sizeof(debug_bgp_as4_segment_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_group_out_cmd__X, &clear_bgp_ipv6_peer_group_out_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_group_out_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_all_tags_cmd__X, &show_ip_bgp_vpnv4_all_tags_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_all_tags_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_vpnv4_out_cmd__X, &clear_ip_bgp_as_vpnv4_out_cmd_bgpd, sizeof(clear_ip_bgp_as_vpnv4_out_cmd_bgpd));
	__activeVars->config_file__X =  NULL;
	memcpy(&__activeVars->no_match_ip_address_val_cmd__X, &no_match_ip_address_val_cmd_bgpd, sizeof(no_match_ip_address_val_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_attr_unchanged10_cmd__X, &no_neighbor_attr_unchanged10_cmd_bgpd, sizeof(no_neighbor_attr_unchanged10_cmd_bgpd));
	memcpy(&__activeVars->peer_af_flag_action_list__X, &peer_af_flag_action_list__T, sizeof(peer_af_flag_action_list__T));
	memcpy(&__activeVars->clear_bgp_ipv6_external_soft_cmd__X, &clear_bgp_ipv6_external_soft_cmd_bgpd, sizeof(clear_bgp_ipv6_external_soft_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_as_in_prefix_filter_cmd__X, &clear_bgp_ipv6_as_in_prefix_filter_cmd_bgpd, sizeof(clear_bgp_ipv6_as_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->no_debug_bgp_fsm_cmd__X, &no_debug_bgp_fsm_cmd_bgpd, sizeof(no_debug_bgp_fsm_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_flap_prefix_cmd__X, &show_ip_bgp_flap_prefix_cmd_bgpd, sizeof(show_ip_bgp_flap_prefix_cmd_bgpd));
	memcpy(&__activeVars->no_debug_bgp_update_cmd__X, &no_debug_bgp_update_cmd_bgpd, sizeof(no_debug_bgp_update_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_mask_natural_ttl_cmd__X, &bgp_network_mask_natural_ttl_cmd_bgpd, sizeof(bgp_network_mask_natural_ttl_cmd_bgpd));
	memcpy(&__activeVars->match_ip_route_source_cmd__X, &match_ip_route_source_cmd_bgpd, sizeof(match_ip_route_source_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_as_in_cmd__X, &clear_bgp_as_in_cmd_bgpd, sizeof(clear_bgp_as_in_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_view_route_cmd__X, &show_ip_bgp_view_route_cmd_bgpd, sizeof(show_ip_bgp_view_route_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_confederation_identifier_arg_cmd__X, &no_bgp_confederation_identifier_arg_cmd_bgpd, sizeof(no_bgp_confederation_identifier_arg_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_cmd__X, &clear_ip_bgp_as_cmd_bgpd, sizeof(clear_ip_bgp_as_cmd_bgpd));
	memcpy(&__activeVars->no_set_ecommunity_rt_val_cmd__X, &no_set_ecommunity_rt_val_cmd_bgpd, sizeof(no_set_ecommunity_rt_val_cmd_bgpd));
	memcpy(&__activeVars->neighbor_attr_unchanged_cmd__X, &neighbor_attr_unchanged_cmd_bgpd, sizeof(neighbor_attr_unchanged_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_neighbors_cmd__X, &show_ip_bgp_neighbors_cmd_bgpd, sizeof(show_ip_bgp_neighbors_cmd_bgpd));
	memcpy(&__activeVars->route_match_peer_cmd__X, &route_match_peer_cmd_bgpd, sizeof(route_match_peer_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_mask_natural_cmd__X, &bgp_network_mask_natural_cmd_bgpd, sizeof(bgp_network_mask_natural_cmd_bgpd));
	memcpy(&__activeVars->debug_bgp_events_cmd__X, &debug_bgp_events_cmd_bgpd, sizeof(debug_bgp_events_cmd_bgpd));
	memcpy(&__activeVars->set_pathlimit_ttl_cmd__X, &set_pathlimit_ttl_cmd_bgpd, sizeof(set_pathlimit_ttl_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_in_prefix_filter_cmd__X, &clear_ip_bgp_as_in_prefix_filter_cmd_bgpd, sizeof(clear_ip_bgp_as_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_all_soft_in_cmd__X, &clear_bgp_all_soft_in_cmd_bgpd, sizeof(clear_bgp_all_soft_in_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_backdoor_ttl_cmd__X, &bgp_network_backdoor_ttl_cmd_bgpd, sizeof(bgp_network_backdoor_ttl_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_paths_cmd__X, &show_ip_bgp_paths_cmd_bgpd, sizeof(show_ip_bgp_paths_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_ipv4_in_cmd__X, &clear_ip_bgp_all_ipv4_in_cmd_bgpd, sizeof(clear_ip_bgp_all_ipv4_in_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_scan_time_val_cmd__X, &no_bgp_scan_time_val_cmd_bgpd, sizeof(no_bgp_scan_time_val_cmd_bgpd));
	memcpy(&__activeVars->no_debug_bgp_all_cmd__X, &no_debug_bgp_all_cmd_bgpd, sizeof(no_debug_bgp_all_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_flap_address_cmd__X, &show_ip_bgp_flap_address_cmd_bgpd, sizeof(show_ip_bgp_flap_address_cmd_bgpd));
	memcpy(&__activeVars->show_ip_extcommunity_list_cmd__X, &show_ip_extcommunity_list_cmd_bgpd, sizeof(show_ip_extcommunity_list_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_external_soft_in_cmd__X, &clear_bgp_ipv6_external_soft_in_cmd_bgpd, sizeof(clear_bgp_ipv6_external_soft_in_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_filter_list_cmd__X, &show_ip_bgp_ipv4_filter_list_cmd_bgpd, sizeof(show_ip_bgp_ipv4_filter_list_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_cluster_id_arg_cmd__X, &no_bgp_cluster_id_arg_cmd_bgpd, sizeof(no_bgp_cluster_id_arg_cmd_bgpd));
	memcpy(&__activeVars->bgp_graceful_restart_stalepath_time_cmd__X, &bgp_graceful_restart_stalepath_time_cmd_bgpd, sizeof(bgp_graceful_restart_stalepath_time_cmd_bgpd));
	memcpy(&__activeVars->set_aspath_exclude_cmd__X, &set_aspath_exclude_cmd_bgpd, sizeof(set_aspath_exclude_cmd_bgpd));
	memcpy(&__activeVars->route_match_ip_address_prefix_list_cmd__X, &route_match_ip_address_prefix_list_cmd_bgpd, sizeof(route_match_ip_address_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->neighbor_passive_cmd__X, &neighbor_passive_cmd_bgpd, sizeof(neighbor_passive_cmd_bgpd));
	memcpy(&__activeVars->neighbor_timers_connect_cmd__X, &neighbor_timers_connect_cmd_bgpd, sizeof(neighbor_timers_connect_cmd_bgpd));
	__activeVars->bgp_notify_msg_max__X =  BGP_NOTIFY_MAX;
	memcpy(&__activeVars->clear_ip_bgp_external_ipv4_soft_out_cmd__X, &clear_ip_bgp_external_ipv4_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_external_ipv4_soft_out_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_group_soft_out_cmd__X, &clear_ip_bgp_peer_group_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_peer_group_soft_out_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_group_soft_cmd__X, &clear_ip_bgp_peer_group_soft_cmd_bgpd, sizeof(clear_ip_bgp_peer_group_soft_cmd_bgpd));
	memcpy(&__activeVars->undebug_bgp_zebra_cmd__X, &undebug_bgp_zebra_cmd_bgpd, sizeof(undebug_bgp_zebra_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_neighbors_peer_cmd__X, &show_ip_bgp_ipv4_neighbors_peer_cmd_bgpd, sizeof(show_ip_bgp_ipv4_neighbors_peer_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_ipv4_soft_cmd__X, &clear_ip_bgp_peer_ipv4_soft_cmd_bgpd, sizeof(clear_ip_bgp_peer_ipv4_soft_cmd_bgpd));
	__activeVars->bgp_notify_head_msg_max__X =  BGP_NOTIFY_HEADER_MAX;
	memcpy(&__activeVars->router_bgp_cmd__X, &router_bgp_cmd_bgpd, sizeof(router_bgp_cmd_bgpd));
	memcpy(&__activeVars->no_debug_bgp_as4_segment_cmd__X, &no_debug_bgp_as4_segment_cmd_bgpd, sizeof(no_debug_bgp_as4_segment_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_out_cmd__X, &clear_ip_bgp_as_out_cmd_bgpd, sizeof(clear_ip_bgp_as_out_cmd_bgpd));
	memcpy(&__activeVars->set_community_cmd__X, &set_community_cmd_bgpd, sizeof(set_community_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_external_cmd__X, &clear_bgp_ipv6_external_cmd_bgpd, sizeof(clear_bgp_ipv6_external_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_mask_natural_cmd__X, &no_bgp_network_mask_natural_cmd_bgpd, sizeof(no_bgp_network_mask_natural_cmd_bgpd));
	memcpy(&__activeVars->no_set_metric_cmd__X, &no_set_metric_cmd_bgpd, sizeof(no_set_metric_cmd_bgpd));
	memcpy(&__activeVars->no_match_ip_route_source_cmd__X, &no_match_ip_route_source_cmd_bgpd, sizeof(no_match_ip_route_source_cmd_bgpd));
	memcpy(&__activeVars->bgp_confederation_peers_cmd__X, &bgp_confederation_peers_cmd_bgpd, sizeof(bgp_confederation_peers_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_neighbors_peer_cmd__X, &show_ip_bgp_neighbors_peer_cmd_bgpd, sizeof(show_ip_bgp_neighbors_peer_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_external_in_prefix_filter_cmd__X, &clear_bgp_external_in_prefix_filter_cmd_bgpd, sizeof(clear_bgp_external_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->undebug_bgp_events_cmd__X, &undebug_bgp_events_cmd_bgpd, sizeof(undebug_bgp_events_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_instance_all_ipv4_in_prefix_filter_cmd__X, &clear_ip_bgp_instance_all_ipv4_in_prefix_filter_cmd_bgpd, sizeof(clear_ip_bgp_instance_all_ipv4_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->bgp_distance_cmd__X, &bgp_distance_cmd_bgpd, sizeof(bgp_distance_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_external_in_cmd__X, &clear_bgp_external_in_cmd_bgpd, sizeof(clear_bgp_external_in_cmd_bgpd));
	memcpy(&__activeVars->neighbor_shutdown_cmd__X, &neighbor_shutdown_cmd_bgpd, sizeof(neighbor_shutdown_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_external_out_cmd__X, &clear_bgp_external_out_cmd_bgpd, sizeof(clear_bgp_external_out_cmd_bgpd));
	__activeVars->zclient__X =  NULL;
	memcpy(&__activeVars->show_ip_bgp_cmd__X, &show_ip_bgp_cmd_bgpd, sizeof(show_ip_bgp_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_remove_private_as_cmd__X, &no_neighbor_remove_private_as_cmd_bgpd, sizeof(no_neighbor_remove_private_as_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_rd_neighbor_routes_cmd__X, &show_ip_bgp_vpnv4_rd_neighbor_routes_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_rd_neighbor_routes_cmd_bgpd));
	memcpy(&__activeVars->neighbor_local_as_no_prepend_cmd__X, &neighbor_local_as_no_prepend_cmd_bgpd, sizeof(neighbor_local_as_no_prepend_cmd_bgpd));
	memcpy(&__activeVars->capcode_str__X, &capcode_str__T, sizeof(capcode_str__T));
	memcpy(&__activeVars->bgp_router_id_cmd__X, &bgp_router_id_cmd_bgpd, sizeof(bgp_router_id_cmd_bgpd));
	memcpy(&__activeVars->aggregate_address_summary_as_set_cmd__X, &aggregate_address_summary_as_set_cmd_bgpd, sizeof(aggregate_address_summary_as_set_cmd_bgpd));
	memcpy(&__activeVars->neighbor_port_cmd__X, &neighbor_port_cmd_bgpd, sizeof(neighbor_port_cmd_bgpd));
	memcpy(&__activeVars->no_debug_bgp_normal_cmd__X, &no_debug_bgp_normal_cmd_bgpd, sizeof(no_debug_bgp_normal_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_override_capability_cmd__X, &no_neighbor_override_capability_cmd_bgpd, sizeof(no_neighbor_override_capability_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_community_list_cmd__X, &show_ip_bgp_community_list_cmd_bgpd, sizeof(show_ip_bgp_community_list_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_rsclient_cmd__X, &clear_ip_bgp_peer_rsclient_cmd_bgpd, sizeof(clear_ip_bgp_peer_rsclient_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_all_soft_cmd__X, &clear_bgp_ipv6_all_soft_cmd_bgpd, sizeof(clear_bgp_ipv6_all_soft_cmd_bgpd));
	memcpy(&__activeVars->debug_bgp_filter_cmd__X, &debug_bgp_filter_cmd_bgpd, sizeof(debug_bgp_filter_cmd_bgpd));
	memcpy(&__activeVars->neighbor_enforce_multihop_cmd__X, &neighbor_enforce_multihop_cmd_bgpd, sizeof(neighbor_enforce_multihop_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_dont_capability_negotiate_cmd__X, &no_neighbor_dont_capability_negotiate_cmd_bgpd, sizeof(no_neighbor_dont_capability_negotiate_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_community_exact_cmd__X, &show_ip_bgp_ipv4_community_exact_cmd_bgpd, sizeof(show_ip_bgp_ipv4_community_exact_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_maximum_prefix_threshold_restart_cmd__X, &no_neighbor_maximum_prefix_threshold_restart_cmd_bgpd, sizeof(no_neighbor_maximum_prefix_threshold_restart_cmd_bgpd));
	memcpy(&__activeVars->neighbor_maximum_prefix_warning_cmd__X, &neighbor_maximum_prefix_warning_cmd_bgpd, sizeof(neighbor_maximum_prefix_warning_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_router_id_val_cmd__X, &no_bgp_router_id_val_cmd_bgpd, sizeof(no_bgp_router_id_val_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_soft_in_cmd__X, &clear_ip_bgp_peer_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_peer_soft_in_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_flap_prefix_list_cmd__X, &show_ip_bgp_flap_prefix_list_cmd_bgpd, sizeof(show_ip_bgp_flap_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->no_match_ip_next_hop_prefix_list_val_cmd__X, &no_match_ip_next_hop_prefix_list_val_cmd_bgpd, sizeof(no_match_ip_next_hop_prefix_list_val_cmd_bgpd));
	memcpy(&__activeVars->undebug_bgp_all_cmd__X, &undebug_bgp_all_cmd_bgpd, sizeof(undebug_bgp_all_cmd_bgpd));
	memcpy(&__activeVars->no_set_atomic_aggregate_cmd__X, &no_set_atomic_aggregate_cmd_bgpd, sizeof(no_set_atomic_aggregate_cmd_bgpd));
	memcpy(&__activeVars->no_set_aspath_exclude_cmd__X, &no_set_aspath_exclude_cmd_bgpd, sizeof(no_set_aspath_exclude_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_ipv6_neighbor_prefix_counts_cmd__X, &show_bgp_ipv6_neighbor_prefix_counts_cmd_bgpd, sizeof(show_bgp_ipv6_neighbor_prefix_counts_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_default_originate_cmd__X, &no_neighbor_default_originate_cmd_bgpd, sizeof(no_neighbor_default_originate_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_dampening_address_cmd__X, &clear_ip_bgp_dampening_address_cmd_bgpd, sizeof(clear_ip_bgp_dampening_address_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_as_soft_cmd__X, &clear_bgp_ipv6_as_soft_cmd_bgpd, sizeof(clear_bgp_ipv6_as_soft_cmd_bgpd));
	memcpy(&__activeVars->no_set_ip_nexthop_cmd__X, &no_set_ip_nexthop_cmd_bgpd, sizeof(no_set_ip_nexthop_cmd_bgpd));
	memcpy(&__activeVars->ip_extcommunity_list_standard2_cmd__X, &ip_extcommunity_list_standard2_cmd_bgpd, sizeof(ip_extcommunity_list_standard2_cmd_bgpd));
	memcpy(&__activeVars->neighbor_maximum_prefix_restart_cmd__X, &neighbor_maximum_prefix_restart_cmd_bgpd, sizeof(neighbor_maximum_prefix_restart_cmd_bgpd));
	memcpy(&__activeVars->route_set_ecommunity_soo_cmd__X, &route_set_ecommunity_soo_cmd_bgpd, sizeof(route_set_ecommunity_soo_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_instance_all_ipv4_soft_cmd__X, &clear_ip_bgp_instance_all_ipv4_soft_cmd_bgpd, sizeof(clear_ip_bgp_instance_all_ipv4_soft_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_rsclient_route_cmd__X, &show_ip_bgp_rsclient_route_cmd_bgpd, sizeof(show_ip_bgp_rsclient_route_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_external_cmd__X, &clear_ip_bgp_external_cmd_bgpd, sizeof(clear_ip_bgp_external_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_vpnv4_soft_cmd__X, &clear_ip_bgp_as_vpnv4_soft_cmd_bgpd, sizeof(clear_ip_bgp_as_vpnv4_soft_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_route_map_cmd__X, &show_ip_bgp_route_map_cmd_bgpd, sizeof(show_ip_bgp_route_map_cmd_bgpd));
	memcpy(&__activeVars->no_set_community_delete_val_cmd__X, &no_set_community_delete_val_cmd_bgpd, sizeof(no_set_community_delete_val_cmd_bgpd));
	memcpy(&__activeVars->neighbor_remove_private_as_cmd__X, &neighbor_remove_private_as_cmd_bgpd, sizeof(neighbor_remove_private_as_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_neighbor_prefix_counts_cmd__X, &show_ip_bgp_ipv4_neighbor_prefix_counts_cmd_bgpd, sizeof(show_ip_bgp_ipv4_neighbor_prefix_counts_cmd_bgpd));
	memcpy(&__activeVars->neighbor_nexthop_local_unchanged_cmd__X, &neighbor_nexthop_local_unchanged_cmd_bgpd, sizeof(neighbor_nexthop_local_unchanged_cmd_bgpd));
	memcpy(&__activeVars->no_ip_community_list_expanded_cmd__X, &no_ip_community_list_expanded_cmd_bgpd, sizeof(no_ip_community_list_expanded_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_dampening_cmd__X, &clear_ip_bgp_dampening_cmd_bgpd, sizeof(clear_ip_bgp_dampening_cmd_bgpd));
	memcpy(&__activeVars->no_ip_extcommunity_list_standard_cmd__X, &no_ip_extcommunity_list_standard_cmd_bgpd, sizeof(no_ip_extcommunity_list_standard_cmd_bgpd));
	memcpy(&__activeVars->no_match_community_val_cmd__X, &no_match_community_val_cmd_bgpd, sizeof(no_match_community_val_cmd_bgpd));
	__activeVars->orf_type_str_max__X =  sizeof(orf_type_str)/sizeof(orf_type_str[0]);
	memcpy(&__activeVars->clear_bgp_external_soft_in_cmd__X, &clear_bgp_external_soft_in_cmd_bgpd, sizeof(clear_bgp_external_soft_in_cmd_bgpd));
	memcpy(&__activeVars->bgp_bestpath_compare_router_id_cmd__X, &bgp_bestpath_compare_router_id_cmd_bgpd, sizeof(bgp_bestpath_compare_router_id_cmd_bgpd));
	memcpy(&__activeVars->match_metric_cmd__X, &match_metric_cmd_bgpd, sizeof(match_metric_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_cmd__X, &no_neighbor_cmd_bgpd, sizeof(no_neighbor_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_statistics_view_vpnv4_cmd__X, &show_bgp_statistics_view_vpnv4_cmd_bgpd, sizeof(show_bgp_statistics_view_vpnv4_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_ipv4_in_cmd__X, &clear_ip_bgp_peer_ipv4_in_cmd_bgpd, sizeof(clear_ip_bgp_peer_ipv4_in_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_all_in_prefix_filter_cmd__X, &clear_bgp_all_in_prefix_filter_cmd_bgpd, sizeof(clear_bgp_all_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_instance_all_soft_in_cmd__X, &clear_ip_bgp_instance_all_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_instance_all_soft_in_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_mask_backdoor_cmd__X, &bgp_network_mask_backdoor_cmd_bgpd, sizeof(bgp_network_mask_backdoor_cmd_bgpd));
	memcpy(&__activeVars->no_match_ecommunity_cmd__X, &no_match_ecommunity_cmd_bgpd, sizeof(no_match_ecommunity_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_bestpath_med3_cmd__X, &no_bgp_bestpath_med3_cmd_bgpd, sizeof(no_bgp_bestpath_med3_cmd_bgpd));
	memcpy(&__activeVars->debug_bgp_keepalive_cmd__X, &debug_bgp_keepalive_cmd_bgpd, sizeof(debug_bgp_keepalive_cmd_bgpd));
	memcpy(&__activeVars->route_set_aspath_prepend_cmd__X, &route_set_aspath_prepend_cmd_bgpd, sizeof(route_set_aspath_prepend_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_as_out_cmd__X, &clear_bgp_ipv6_as_out_cmd_bgpd, sizeof(clear_bgp_ipv6_as_out_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_route_cmd__X, &show_ip_bgp_ipv4_route_cmd_bgpd, sizeof(show_ip_bgp_ipv4_route_cmd_bgpd));
	memcpy(&__activeVars->dump_bgp_routes_cmd__X, &dump_bgp_routes_cmd_bgpd, sizeof(dump_bgp_routes_cmd_bgpd));
	memcpy(&__activeVars->route_match_community_cmd__X, &route_match_community_cmd_bgpd, sizeof(route_match_community_cmd_bgpd));
	memcpy(&__activeVars->no_match_aspath_val_cmd__X, &no_match_aspath_val_cmd_bgpd, sizeof(no_match_aspath_val_cmd_bgpd));
	memcpy(&__activeVars->no_set_origin_cmd__X, &no_set_origin_cmd_bgpd, sizeof(no_set_origin_cmd_bgpd));
	memcpy(&__activeVars->neighbor_attr_unchanged8_cmd__X, &neighbor_attr_unchanged8_cmd_bgpd, sizeof(neighbor_attr_unchanged8_cmd_bgpd));
	memcpy(&__activeVars->no_ip_extcommunity_list_name_expanded_all_cmd__X, &no_ip_extcommunity_list_name_expanded_all_cmd_bgpd, sizeof(no_ip_extcommunity_list_name_expanded_all_cmd_bgpd));
	memcpy(&__activeVars->no_synchronization_cmd__X, &no_synchronization_cmd_bgpd, sizeof(no_synchronization_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_community_list_cmd__X, &show_ip_bgp_ipv4_community_list_cmd_bgpd, sizeof(show_ip_bgp_ipv4_community_list_cmd_bgpd));
	memcpy(&__activeVars->neighbor_capability_dynamic_cmd__X, &neighbor_capability_dynamic_cmd_bgpd, sizeof(neighbor_capability_dynamic_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_group_soft_in_cmd__X, &clear_ip_bgp_peer_group_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_peer_group_soft_in_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_description_val_cmd__X, &no_neighbor_description_val_cmd_bgpd, sizeof(no_neighbor_description_val_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_instance_all_soft_cmd__X, &clear_bgp_instance_all_soft_cmd_bgpd, sizeof(clear_bgp_instance_all_soft_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_group_cmd__X, &clear_ip_bgp_peer_group_cmd_bgpd, sizeof(clear_ip_bgp_peer_group_cmd_bgpd));
	memcpy(&__activeVars->no_aggregate_address_mask_summary_as_set_cmd__X, &no_aggregate_address_mask_summary_as_set_cmd_bgpd, sizeof(no_aggregate_address_mask_summary_as_set_cmd_bgpd));
	memcpy(&__activeVars->match_ip_address_cmd__X, &match_ip_address_cmd_bgpd, sizeof(match_ip_address_cmd_bgpd));
	memcpy(&__activeVars->no_set_originator_id_val_cmd__X, &no_set_originator_id_val_cmd_bgpd, sizeof(no_set_originator_id_val_cmd_bgpd));
	memcpy(&__activeVars->no_aggregate_address_summary_as_set_cmd__X, &no_aggregate_address_summary_as_set_cmd_bgpd, sizeof(no_aggregate_address_summary_as_set_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_cidr_only_cmd__X, &show_ip_bgp_ipv4_cidr_only_cmd_bgpd, sizeof(show_ip_bgp_ipv4_cidr_only_cmd_bgpd));
	memcpy(&__activeVars->set_local_pref_cmd__X, &set_local_pref_cmd_bgpd, sizeof(set_local_pref_cmd_bgpd));
	memcpy(&__activeVars->set_aggregator_as_cmd__X, &set_aggregator_as_cmd_bgpd, sizeof(set_aggregator_as_cmd_bgpd));
	memcpy(&__activeVars->bgp_bestpath_med_cmd__X, &bgp_bestpath_med_cmd_bgpd, sizeof(bgp_bestpath_med_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_soft_in_cmd__X, &clear_ip_bgp_as_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_as_soft_in_cmd_bgpd));
	memcpy(&__activeVars->route_match_ip_route_source_prefix_list_cmd__X, &route_match_ip_route_source_prefix_list_cmd_bgpd, sizeof(route_match_ip_route_source_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->bgp_bestpath_med2_cmd__X, &bgp_bestpath_med2_cmd_bgpd, sizeof(bgp_bestpath_med2_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_local_as_cmd__X, &no_neighbor_local_as_cmd_bgpd, sizeof(no_neighbor_local_as_cmd_bgpd));
	memcpy(&__activeVars->neighbor_attr_unchanged3_cmd__X, &neighbor_attr_unchanged3_cmd_bgpd, sizeof(neighbor_attr_unchanged3_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_attr_unchanged7_cmd__X, &no_neighbor_attr_unchanged7_cmd_bgpd, sizeof(no_neighbor_attr_unchanged7_cmd_bgpd));
	memcpy(&__activeVars->neighbor_attr_unchanged7_cmd__X, &neighbor_attr_unchanged7_cmd_bgpd, sizeof(neighbor_attr_unchanged7_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_enforce_first_as_cmd__X, &no_bgp_enforce_first_as_cmd_bgpd, sizeof(no_bgp_enforce_first_as_cmd_bgpd));
	memcpy(&__activeVars->no_aggregate_address_mask_summary_only_cmd__X, &no_aggregate_address_mask_summary_only_cmd_bgpd, sizeof(no_aggregate_address_mask_summary_only_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_vpnv4_in_cmd__X, &clear_ip_bgp_as_vpnv4_in_cmd_bgpd, sizeof(clear_ip_bgp_as_vpnv4_in_cmd_bgpd));
	memcpy(&__activeVars->bgp_vpnv4_node__X, &bgp_vpnv4_node__T, sizeof(bgp_vpnv4_node__T));
	memcpy(&__activeVars->no_neighbor_unsuppress_map_cmd__X, &no_neighbor_unsuppress_map_cmd_bgpd, sizeof(no_neighbor_unsuppress_map_cmd_bgpd));
	memcpy(&__activeVars->undebug_bgp_as4_segment_cmd__X, &undebug_bgp_as4_segment_cmd_bgpd, sizeof(undebug_bgp_as4_segment_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_route_map_cmd__X, &no_neighbor_route_map_cmd_bgpd, sizeof(no_neighbor_route_map_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_group_in_prefix_filter_cmd__X, &clear_ip_bgp_peer_group_in_prefix_filter_cmd_bgpd, sizeof(clear_ip_bgp_peer_group_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->no_debug_bgp_zebra_cmd__X, &no_debug_bgp_zebra_cmd_bgpd, sizeof(no_debug_bgp_zebra_cmd_bgpd));
	memcpy(&__activeVars->route_set_community_delete_cmd__X, &route_set_community_delete_cmd_bgpd, sizeof(route_set_community_delete_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_ipv6_neighbors_peer_cmd__X, &show_bgp_ipv6_neighbors_peer_cmd_bgpd, sizeof(show_bgp_ipv6_neighbors_peer_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_group_ipv4_soft_cmd__X, &clear_ip_bgp_peer_group_ipv4_soft_cmd_bgpd, sizeof(clear_ip_bgp_peer_group_ipv4_soft_cmd_bgpd));
	memcpy(&__activeVars->neighbor_allowas_in_cmd__X, &neighbor_allowas_in_cmd_bgpd, sizeof(neighbor_allowas_in_cmd_bgpd));
	memcpy(&__activeVars->no_auto_summary_cmd__X, &no_auto_summary_cmd_bgpd, sizeof(no_auto_summary_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_mask_natural_backdoor_ttl_cmd__X, &bgp_network_mask_natural_backdoor_ttl_cmd_bgpd, sizeof(bgp_network_mask_natural_backdoor_ttl_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_capability_dynamic_cmd__X, &no_neighbor_capability_dynamic_cmd_bgpd, sizeof(no_neighbor_capability_dynamic_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_peer_soft_cmd__X, &clear_bgp_peer_soft_cmd_bgpd, sizeof(clear_bgp_peer_soft_cmd_bgpd));
	memcpy(&__activeVars->show_ip_extcommunity_list_arg_cmd__X, &show_ip_extcommunity_list_arg_cmd_bgpd, sizeof(show_ip_extcommunity_list_arg_cmd_bgpd));
	memcpy(&__activeVars->bgp_bestpath_aspath_ignore_cmd__X, &bgp_bestpath_aspath_ignore_cmd_bgpd, sizeof(bgp_bestpath_aspath_ignore_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_all_neighbors_peer_cmd__X, &show_ip_bgp_vpnv4_all_neighbors_peer_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_all_neighbors_peer_cmd_bgpd));
	memcpy(&__activeVars->set_originator_id_cmd__X, &set_originator_id_cmd_bgpd, sizeof(set_originator_id_cmd_bgpd));
	memcpy(&__activeVars->ip_community_list_name_expanded_cmd__X, &ip_community_list_name_expanded_cmd_bgpd, sizeof(ip_community_list_name_expanded_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_vpnv4_out_cmd__X, &clear_ip_bgp_all_vpnv4_out_cmd_bgpd, sizeof(clear_ip_bgp_all_vpnv4_out_cmd_bgpd));
	memcpy(&__activeVars->route_match_ip_address_cmd__X, &route_match_ip_address_cmd_bgpd, sizeof(route_match_ip_address_cmd_bgpd));
	__activeVars->bgp_status_msg_max__X =  BGP_STATUS_MAX;
	memcpy(&__activeVars->clear_ip_bgp_as_ipv4_out_cmd__X, &clear_ip_bgp_as_ipv4_out_cmd_bgpd, sizeof(clear_ip_bgp_as_ipv4_out_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_view_rsclient_route_cmd__X, &show_ip_bgp_view_rsclient_route_cmd_bgpd, sizeof(show_ip_bgp_view_rsclient_route_cmd_bgpd));
	memcpy(&__activeVars->no_match_peer_val_cmd__X, &no_match_peer_val_cmd_bgpd, sizeof(no_match_peer_val_cmd_bgpd));
	memcpy(&__activeVars->no_debug_bgp_filter_cmd__X, &no_debug_bgp_filter_cmd_bgpd, sizeof(no_debug_bgp_filter_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_community_cmd__X, &show_ip_bgp_ipv4_community_cmd_bgpd, sizeof(show_ip_bgp_ipv4_community_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_all_neighbor_routes_cmd__X, &show_ip_bgp_vpnv4_all_neighbor_routes_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_all_neighbor_routes_cmd_bgpd));
	memcpy(&__activeVars->route_set_origin_cmd__X, &route_set_origin_cmd_bgpd, sizeof(route_set_origin_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_disable_connected_check_cmd__X, &no_neighbor_disable_connected_check_cmd_bgpd, sizeof(no_neighbor_disable_connected_check_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_community2_exact_cmd__X, &show_ip_bgp_community2_exact_cmd_bgpd, sizeof(show_ip_bgp_community2_exact_cmd_bgpd));
	memcpy(&__activeVars->no_set_community_none_cmd__X, &no_set_community_none_cmd_bgpd, sizeof(no_set_community_none_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_flap_regexp_cmd__X, &show_ip_bgp_flap_regexp_cmd_bgpd, sizeof(show_ip_bgp_flap_regexp_cmd_bgpd));
	memcpy(&__activeVars->neighbor_password_cmd__X, &neighbor_password_cmd_bgpd, sizeof(neighbor_password_cmd_bgpd));
	memcpy(&__activeVars->bgp_redistribute_ipv4_rmap_metric_cmd__X, &bgp_redistribute_ipv4_rmap_metric_cmd_bgpd, sizeof(bgp_redistribute_ipv4_rmap_metric_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_community_info_cmd__X, &show_ip_bgp_community_info_cmd_bgpd, sizeof(show_ip_bgp_community_info_cmd_bgpd));
	memcpy(&__activeVars->no_set_aggregator_as_val_cmd__X, &no_set_aggregator_as_val_cmd_bgpd, sizeof(no_set_aggregator_as_val_cmd_bgpd));
	memcpy(&__activeVars->bgp_bestpath_aspath_confed_cmd__X, &bgp_bestpath_aspath_confed_cmd_bgpd, sizeof(bgp_bestpath_aspath_confed_cmd_bgpd));
	memcpy(&__activeVars->neighbor_attr_unchanged9_cmd__X, &neighbor_attr_unchanged9_cmd_bgpd, sizeof(neighbor_attr_unchanged9_cmd_bgpd));
	memcpy(&__activeVars->no_set_ecommunity_soo_val_cmd__X, &no_set_ecommunity_soo_val_cmd_bgpd, sizeof(no_set_ecommunity_soo_val_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_group_ipv4_soft_out_cmd__X, &clear_ip_bgp_peer_group_ipv4_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_peer_group_ipv4_soft_out_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_instance_neighbors_peer_cmd__X, &show_ip_bgp_instance_neighbors_peer_cmd_bgpd, sizeof(show_ip_bgp_instance_neighbors_peer_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_out_cmd__X, &clear_bgp_ipv6_peer_out_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_out_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_always_compare_med_cmd__X, &no_bgp_always_compare_med_cmd_bgpd, sizeof(no_bgp_always_compare_med_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_as_soft_out_cmd__X, &clear_bgp_ipv6_as_soft_out_cmd_bgpd, sizeof(clear_bgp_ipv6_as_soft_out_cmd_bgpd));
	memcpy(&__activeVars->set_origin_cmd__X, &set_origin_cmd_bgpd, sizeof(set_origin_cmd_bgpd));
	memcpy(&__activeVars->neighbor_disable_connected_check_cmd__X, &neighbor_disable_connected_check_cmd_bgpd, sizeof(neighbor_disable_connected_check_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_external_in_prefix_filter_cmd__X, &clear_ip_bgp_external_in_prefix_filter_cmd_bgpd, sizeof(clear_ip_bgp_external_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_cmd__X, &clear_ip_bgp_all_cmd_bgpd, sizeof(clear_ip_bgp_all_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_vpnv4_soft_in_cmd__X, &clear_ip_bgp_peer_vpnv4_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_peer_vpnv4_soft_in_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_all_soft_in_cmd__X, &clear_bgp_ipv6_all_soft_in_cmd_bgpd, sizeof(clear_bgp_ipv6_all_soft_in_cmd_bgpd));
	memcpy(&__activeVars->show_ip_as_path_access_list_cmd__X, &show_ip_as_path_access_list_cmd_bgpd, sizeof(show_ip_as_path_access_list_cmd_bgpd));
	memcpy(&__activeVars->route_match_origin_cmd__X, &route_match_origin_cmd_bgpd, sizeof(route_match_origin_cmd_bgpd));
	memcpy(&__activeVars->set_ecommunity_rt_cmd__X, &set_ecommunity_rt_cmd_bgpd, sizeof(set_ecommunity_rt_cmd_bgpd));
	memcpy(&__activeVars->neighbor_local_as_cmd__X, &neighbor_local_as_cmd_bgpd, sizeof(neighbor_local_as_cmd_bgpd));
	memcpy(&__activeVars->no_ip_extcommunity_list_standard_all_cmd__X, &no_ip_extcommunity_list_standard_all_cmd_bgpd, sizeof(no_ip_extcommunity_list_standard_all_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_cidr_only_cmd__X, &show_ip_bgp_cidr_only_cmd_bgpd, sizeof(show_ip_bgp_cidr_only_cmd_bgpd));
	memcpy(&__activeVars->bgp_ipv4_unicast_node__X, &bgp_ipv4_unicast_node__T, sizeof(bgp_ipv4_unicast_node__T));
	memcpy(&__activeVars->neighbor_route_map_cmd__X, &neighbor_route_map_cmd_bgpd, sizeof(neighbor_route_map_cmd_bgpd));
	memcpy(&__activeVars->bgp_ipv6_multicast_node__X, &bgp_ipv6_multicast_node__T, sizeof(bgp_ipv6_multicast_node__T));
	memcpy(&__activeVars->neighbor_transparent_as_cmd__X, &neighbor_transparent_as_cmd_bgpd, sizeof(neighbor_transparent_as_cmd_bgpd));
	memcpy(&__activeVars->ip_extcommunity_list_expanded_cmd__X, &ip_extcommunity_list_expanded_cmd_bgpd, sizeof(ip_extcommunity_list_expanded_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_route_cmd__X, &show_ip_bgp_route_cmd_bgpd, sizeof(show_ip_bgp_route_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_external_ipv4_in_prefix_filter_cmd__X, &clear_ip_bgp_external_ipv4_in_prefix_filter_cmd_bgpd, sizeof(clear_ip_bgp_external_ipv4_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_vpnv4_rd_neighbor_advertised_routes_cmd__X, &show_ip_bgp_vpnv4_rd_neighbor_advertised_routes_cmd_bgpd, sizeof(show_ip_bgp_vpnv4_rd_neighbor_advertised_routes_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_network_mask_cmd__X, &no_bgp_network_mask_cmd_bgpd, sizeof(no_bgp_network_mask_cmd_bgpd));
	memcpy(&__activeVars->bgp_damp_unset_cmd__X, &bgp_damp_unset_cmd_bgpd, sizeof(bgp_damp_unset_cmd_bgpd));
	memcpy(&__activeVars->no_aggregate_address_summary_only_cmd__X, &no_aggregate_address_summary_only_cmd_bgpd, sizeof(no_aggregate_address_summary_only_cmd_bgpd));
	memcpy(&__activeVars->neighbor_capability_orf_prefix_cmd__X, &neighbor_capability_orf_prefix_cmd_bgpd, sizeof(neighbor_capability_orf_prefix_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_external_ipv4_soft_cmd__X, &clear_ip_bgp_external_ipv4_soft_cmd_bgpd, sizeof(clear_ip_bgp_external_ipv4_soft_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_instance_all_soft_out_cmd__X, &clear_ip_bgp_instance_all_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_instance_all_soft_out_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_neighbor_received_prefix_filter_cmd__X, &show_ip_bgp_neighbor_received_prefix_filter_cmd_bgpd, sizeof(show_ip_bgp_neighbor_received_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_set_peer_group_cmd__X, &no_neighbor_set_peer_group_cmd_bgpd, sizeof(no_neighbor_set_peer_group_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_mask_route_map_cmd__X, &bgp_network_mask_route_map_cmd_bgpd, sizeof(bgp_network_mask_route_map_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_group_in_cmd__X, &clear_bgp_ipv6_peer_group_in_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_group_in_cmd_bgpd));
	memcpy(&__activeVars->bgp_dump_node__X, &bgp_dump_node__T, sizeof(bgp_dump_node__T));
	memcpy(&__activeVars->aggregate_address_as_set_cmd__X, &aggregate_address_as_set_cmd_bgpd, sizeof(aggregate_address_as_set_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_all_in_cmd__X, &clear_bgp_all_in_cmd_bgpd, sizeof(clear_bgp_all_in_cmd_bgpd));
	memcpy(&__activeVars->bgp_damp_set_cmd__X, &bgp_damp_set_cmd_bgpd, sizeof(bgp_damp_set_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_peer_group_remote_as_cmd__X, &no_neighbor_peer_group_remote_as_cmd_bgpd, sizeof(no_neighbor_peer_group_remote_as_cmd_bgpd));
	memcpy(&__activeVars->orf_mode_str__X, &orf_mode_str__T, sizeof(orf_mode_str__T));
	memcpy(&__activeVars->no_dump_bgp_routes_cmd__X, &no_dump_bgp_routes_cmd_bgpd, sizeof(no_dump_bgp_routes_cmd_bgpd));
	memcpy(&__activeVars->no_aggregate_address_mask_as_set_cmd__X, &no_aggregate_address_mask_as_set_cmd_bgpd, sizeof(no_aggregate_address_mask_as_set_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_community4_cmd__X, &show_ip_bgp_ipv4_community4_cmd_bgpd, sizeof(show_ip_bgp_ipv4_community4_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_confederation_peers_cmd__X, &no_bgp_confederation_peers_cmd_bgpd, sizeof(no_bgp_confederation_peers_cmd_bgpd));
	memcpy(&__activeVars->no_set_weight_val_cmd__X, &no_set_weight_val_cmd_bgpd, sizeof(no_set_weight_val_cmd_bgpd));
	memcpy(&__activeVars->bgp_graceful_restart_cmd__X, &bgp_graceful_restart_cmd_bgpd, sizeof(bgp_graceful_restart_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_community_list_exact_cmd__X, &show_ip_bgp_ipv4_community_list_exact_cmd_bgpd, sizeof(show_ip_bgp_ipv4_community_list_exact_cmd_bgpd));
	memcpy(&__activeVars->no_match_metric_val_cmd__X, &no_match_metric_val_cmd_bgpd, sizeof(no_match_metric_val_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_neighbor_prefix_counts_cmd__X, &show_ip_bgp_neighbor_prefix_counts_cmd_bgpd, sizeof(show_ip_bgp_neighbor_prefix_counts_cmd_bgpd));
	memcpy(&__activeVars->bgp_scan_time_cmd__X, &bgp_scan_time_cmd_bgpd, sizeof(bgp_scan_time_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_community3_exact_cmd__X, &show_ip_bgp_ipv4_community3_exact_cmd_bgpd, sizeof(show_ip_bgp_ipv4_community3_exact_cmd_bgpd));
	memcpy(&__activeVars->pcount_strs__X, &pcount_strs__T, sizeof(pcount_strs__T));
	memcpy(&__activeVars->no_set_aspath_prepend_val_cmd__X, &no_set_aspath_prepend_val_cmd_bgpd, sizeof(no_set_aspath_prepend_val_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_attr_unchanged4_cmd__X, &no_neighbor_attr_unchanged4_cmd_bgpd, sizeof(no_neighbor_attr_unchanged4_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_peer_vpnv4_in_cmd__X, &clear_ip_bgp_peer_vpnv4_in_cmd_bgpd, sizeof(clear_ip_bgp_peer_vpnv4_in_cmd_bgpd));
	memcpy(&__activeVars->bgp_ipv6_unicast_node__X, &bgp_ipv6_unicast_node__T, sizeof(bgp_ipv6_unicast_node__T));
	__activeVars->bgp_notify_update_msg_max__X =  BGP_NOTIFY_UPDATE_MAX;
	memcpy(&__activeVars->clear_bgp_ipv6_external_soft_out_cmd__X, &clear_bgp_ipv6_external_soft_out_cmd_bgpd, sizeof(clear_bgp_ipv6_external_soft_out_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_instance_ipv6_neighbors_cmd__X, &show_bgp_instance_ipv6_neighbors_cmd_bgpd, sizeof(show_bgp_instance_ipv6_neighbors_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_ipv4_in_prefix_filter_cmd__X, &clear_ip_bgp_as_ipv4_in_prefix_filter_cmd_bgpd, sizeof(clear_ip_bgp_as_ipv4_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->neighbor_attr_unchanged5_cmd__X, &neighbor_attr_unchanged5_cmd_bgpd, sizeof(neighbor_attr_unchanged5_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_instance_neighbors_cmd__X, &show_ip_bgp_instance_neighbors_cmd_bgpd, sizeof(show_ip_bgp_instance_neighbors_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_default_local_preference_val_cmd__X, &no_bgp_default_local_preference_val_cmd_bgpd, sizeof(no_bgp_default_local_preference_val_cmd_bgpd));
	memcpy(&__activeVars->bgp_cluster_id_cmd__X, &bgp_cluster_id_cmd_bgpd, sizeof(bgp_cluster_id_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_vpnv4_in_cmd__X, &clear_ip_bgp_all_vpnv4_in_cmd_bgpd, sizeof(clear_ip_bgp_all_vpnv4_in_cmd_bgpd));
	memcpy(&__activeVars->bgp_redistribute_ipv4_metric_cmd__X, &bgp_redistribute_ipv4_metric_cmd_bgpd, sizeof(bgp_redistribute_ipv4_metric_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_ipv4_soft_out_cmd__X, &clear_ip_bgp_all_ipv4_soft_out_cmd_bgpd, sizeof(clear_ip_bgp_all_ipv4_soft_out_cmd_bgpd));
	memcpy(&__activeVars->set_ecommunity_soo_cmd__X, &set_ecommunity_soo_cmd_bgpd, sizeof(set_ecommunity_soo_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_import_check_cmd__X, &bgp_network_import_check_cmd_bgpd, sizeof(bgp_network_import_check_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_instance_all_cmd__X, &clear_bgp_instance_all_cmd_bgpd, sizeof(clear_bgp_instance_all_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_as_soft_in_cmd__X, &clear_bgp_as_soft_in_cmd_bgpd, sizeof(clear_bgp_as_soft_in_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_peer_group_soft_out_cmd__X, &clear_bgp_ipv6_peer_group_soft_out_cmd_bgpd, sizeof(clear_bgp_ipv6_peer_group_soft_out_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_timers_cmd__X, &no_neighbor_timers_cmd_bgpd, sizeof(no_neighbor_timers_cmd_bgpd));
	memcpy(&__activeVars->bgp_cluster_id32_cmd__X, &bgp_cluster_id32_cmd_bgpd, sizeof(bgp_cluster_id32_cmd_bgpd));
	memcpy(&__activeVars->bgp_always_compare_med_cmd__X, &bgp_always_compare_med_cmd_bgpd, sizeof(bgp_always_compare_med_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_rsclient_summary_cmd__X, &show_ip_bgp_ipv4_rsclient_summary_cmd_bgpd, sizeof(show_ip_bgp_ipv4_rsclient_summary_cmd_bgpd));
	memcpy(&__activeVars->aggregate_address_mask_summary_as_set_cmd__X, &aggregate_address_mask_summary_as_set_cmd_bgpd, sizeof(aggregate_address_mask_summary_as_set_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_community3_cmd__X, &show_ip_bgp_ipv4_community3_cmd_bgpd, sizeof(show_ip_bgp_ipv4_community3_cmd_bgpd));
	memcpy(&__activeVars->match_ip_next_hop_cmd__X, &match_ip_next_hop_cmd_bgpd, sizeof(match_ip_next_hop_cmd_bgpd));
	memcpy(&__activeVars->neighbor_attr_unchanged2_cmd__X, &neighbor_attr_unchanged2_cmd_bgpd, sizeof(neighbor_attr_unchanged2_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_all_soft_cmd__X, &clear_bgp_all_soft_cmd_bgpd, sizeof(clear_bgp_all_soft_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_prefix_longer_cmd__X, &show_ip_bgp_ipv4_prefix_longer_cmd_bgpd, sizeof(show_ip_bgp_ipv4_prefix_longer_cmd_bgpd));
	memcpy(&__activeVars->no_aggregate_address_mask_cmd__X, &no_aggregate_address_mask_cmd_bgpd, sizeof(no_aggregate_address_mask_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_deterministic_med_cmd__X, &no_bgp_deterministic_med_cmd_bgpd, sizeof(no_bgp_deterministic_med_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_ipv4_community2_cmd__X, &show_ip_bgp_ipv4_community2_cmd_bgpd, sizeof(show_ip_bgp_ipv4_community2_cmd_bgpd));
	memcpy(&__activeVars->no_match_ip_address_prefix_list_cmd__X, &no_match_ip_address_prefix_list_cmd_bgpd, sizeof(no_match_ip_address_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->match_pathlimit_as_cmd__X, &match_pathlimit_as_cmd_bgpd, sizeof(match_pathlimit_as_cmd_bgpd));
	memcpy(&__activeVars->address_family_ipv4_cmd__X, &address_family_ipv4_cmd_bgpd, sizeof(address_family_ipv4_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_redistribute_ipv4_metric_rmap_cmd__X, &no_bgp_redistribute_ipv4_metric_rmap_cmd_bgpd, sizeof(no_bgp_redistribute_ipv4_metric_rmap_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_graceful_restart_stalepath_time_cmd__X, &no_bgp_graceful_restart_stalepath_time_cmd_bgpd, sizeof(no_bgp_graceful_restart_stalepath_time_cmd_bgpd));
	memcpy(&__activeVars->ip_extcommunity_list_name_standard_cmd__X, &ip_extcommunity_list_name_standard_cmd_bgpd, sizeof(ip_extcommunity_list_name_standard_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_cluster_id_cmd__X, &no_bgp_cluster_id_cmd_bgpd, sizeof(no_bgp_cluster_id_cmd_bgpd));
	memcpy(&__activeVars->bgp_ipv4_multicast_node__X, &bgp_ipv4_multicast_node__T, sizeof(bgp_ipv4_multicast_node__T));
	memcpy(&__activeVars->clear_bgp_peer_group_soft_in_cmd__X, &clear_bgp_peer_group_soft_in_cmd_bgpd, sizeof(clear_bgp_peer_group_soft_in_cmd_bgpd));
	memcpy(&__activeVars->match_aspath_cmd__X, &match_aspath_cmd_bgpd, sizeof(match_aspath_cmd_bgpd));
	memcpy(&__activeVars->neighbor_ebgp_multihop_cmd__X, &neighbor_ebgp_multihop_cmd_bgpd, sizeof(neighbor_ebgp_multihop_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_community4_exact_cmd__X, &show_ip_bgp_community4_exact_cmd_bgpd, sizeof(show_ip_bgp_community4_exact_cmd_bgpd));
	memcpy(&__activeVars->no_set_aspath_prepend_cmd__X, &no_set_aspath_prepend_cmd_bgpd, sizeof(no_set_aspath_prepend_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_ipv6_all_in_cmd__X, &clear_bgp_ipv6_all_in_cmd_bgpd, sizeof(clear_bgp_ipv6_all_in_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_all_soft_in_cmd__X, &clear_ip_bgp_all_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_all_soft_in_cmd_bgpd));
	memcpy(&__activeVars->ip_extcommunity_list_name_standard2_cmd__X, &ip_extcommunity_list_name_standard2_cmd_bgpd, sizeof(ip_extcommunity_list_name_standard2_cmd_bgpd));
	memcpy(&__activeVars->table_stats_strs__X, &table_stats_strs__T, sizeof(table_stats_strs__T));
	memcpy(&__activeVars->ip_community_list_standard_cmd__X, &ip_community_list_standard_cmd_bgpd, sizeof(ip_community_list_standard_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_all_soft_out_cmd__X, &clear_bgp_all_soft_out_cmd_bgpd, sizeof(clear_bgp_all_soft_out_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_advertise_interval_val_cmd__X, &no_neighbor_advertise_interval_val_cmd_bgpd, sizeof(no_neighbor_advertise_interval_val_cmd_bgpd));
	memcpy(&__activeVars->no_match_aspath_cmd__X, &no_match_aspath_cmd_bgpd, sizeof(no_match_aspath_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_peer_soft_in_cmd__X, &clear_bgp_peer_soft_in_cmd_bgpd, sizeof(clear_bgp_peer_soft_in_cmd_bgpd));
	memcpy(&__activeVars->match_peer_cmd__X, &match_peer_cmd_bgpd, sizeof(match_peer_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_instance_rsclient_summary_cmd__X, &show_ip_bgp_instance_rsclient_summary_cmd_bgpd, sizeof(show_ip_bgp_instance_rsclient_summary_cmd_bgpd));
	memcpy(&__activeVars->route_match_ecommunity_cmd__X, &route_match_ecommunity_cmd_bgpd, sizeof(route_match_ecommunity_cmd_bgpd));
	memcpy(&__activeVars->neighbor_weight_cmd__X, &neighbor_weight_cmd_bgpd, sizeof(neighbor_weight_cmd_bgpd));
	memcpy(&__activeVars->neighbor_capability_route_refresh_cmd__X, &neighbor_capability_route_refresh_cmd_bgpd, sizeof(neighbor_capability_route_refresh_cmd_bgpd));
	memcpy(&__activeVars->clear_bgp_peer_group_in_prefix_filter_cmd__X, &clear_bgp_peer_group_in_prefix_filter_cmd_bgpd, sizeof(clear_bgp_peer_group_in_prefix_filter_cmd_bgpd));
	memcpy(&__activeVars->bgp_distance_source_cmd__X, &bgp_distance_source_cmd_bgpd, sizeof(bgp_distance_source_cmd_bgpd));
	memcpy(&__activeVars->bgp_damp_unset2_cmd__X, &bgp_damp_unset2_cmd_bgpd, sizeof(bgp_damp_unset2_cmd_bgpd));
	memcpy(&__activeVars->clear_ip_bgp_as_vpnv4_soft_in_cmd__X, &clear_ip_bgp_as_vpnv4_soft_in_cmd_bgpd, sizeof(clear_ip_bgp_as_vpnv4_soft_in_cmd_bgpd));
	memcpy(&__activeVars->no_ip_extcommunity_list_name_standard_cmd__X, &no_ip_extcommunity_list_name_standard_cmd_bgpd, sizeof(no_ip_extcommunity_list_name_standard_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_view_rsclient_prefix_cmd__X, &show_ip_bgp_view_rsclient_prefix_cmd_bgpd, sizeof(show_ip_bgp_view_rsclient_prefix_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_local_as_val_cmd__X, &no_neighbor_local_as_val_cmd_bgpd, sizeof(no_neighbor_local_as_val_cmd_bgpd));
	memcpy(&__activeVars->no_ip_community_list_expanded_all_cmd__X, &no_ip_community_list_expanded_all_cmd_bgpd, sizeof(no_ip_community_list_expanded_all_cmd_bgpd));
	memcpy(&__activeVars->no_neighbor_prefix_list_cmd__X, &no_neighbor_prefix_list_cmd_bgpd, sizeof(no_neighbor_prefix_list_cmd_bgpd));
	memcpy(&__activeVars->no_bgp_timers_cmd__X, &no_bgp_timers_cmd_bgpd, sizeof(no_bgp_timers_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_route_map_cmd__X, &bgp_network_route_map_cmd_bgpd, sizeof(bgp_network_route_map_cmd_bgpd));
	memcpy(&__activeVars->bgp_redistribute_ipv4_metric_rmap_cmd__X, &bgp_redistribute_ipv4_metric_rmap_cmd_bgpd, sizeof(bgp_redistribute_ipv4_metric_rmap_cmd_bgpd));
	memcpy(&__activeVars->bgp_network_mask_backdoor_ttl_cmd__X, &bgp_network_mask_backdoor_ttl_cmd_bgpd, sizeof(bgp_network_mask_backdoor_ttl_cmd_bgpd));
	memcpy(&__activeVars->show_ip_bgp_neighbor_damp_cmd__X, &show_ip_bgp_neighbor_damp_cmd_bgpd, sizeof(show_ip_bgp_neighbor_damp_cmd_bgpd));
	memcpy(&__activeVars->show_bgp_route_map_cmd__X, &show_bgp_route_map_cmd_bgpd, sizeof(show_bgp_route_map_cmd_bgpd));
	memcpy(&__activeVars->neighbor_nexthop_self_cmd__X, &neighbor_nexthop_self_cmd_bgpd, sizeof(neighbor_nexthop_self_cmd_bgpd));
}

