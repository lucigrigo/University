
################################################################
# This is a generated script based on design: diszain
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

namespace eval _tcl {
proc get_script_folder {} {
   set script_path [file normalize [info script]]
   set script_folder [file dirname $script_path]
   return $script_folder
}
}
variable script_folder
set script_folder [_tcl::get_script_folder]

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2019.2
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   catch {common::send_msg_id "BD_TCL-109" "ERROR" "This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."}

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source diszain_script.tcl

# If there is no project opened, this script will create a
# project, but make sure you do not have an existing project
# <./myproj/project_1.xpr> in the current working folder.

set list_projs [get_projects -quiet]
if { $list_projs eq "" } {
   create_project project_1 myproj -part xc7a100tcsg324-1
}


# CHANGE DESIGN NAME HERE
variable design_name
set design_name diszain

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      common::send_msg_id "BD_TCL-001" "INFO" "Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   common::send_msg_id "BD_TCL-002" "INFO" "Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   common::send_msg_id "BD_TCL-003" "INFO" "Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   common::send_msg_id "BD_TCL-004" "INFO" "Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

common::send_msg_id "BD_TCL-005" "INFO" "Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   catch {common::send_msg_id "BD_TCL-114" "ERROR" $errMsg}
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  variable script_folder
  variable design_name

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     catch {common::send_msg_id "BD_TCL-100" "ERROR" "Unable to find parent cell <$parentCell>!"}
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     catch {common::send_msg_id "BD_TCL-101" "ERROR" "Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."}
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports

  # Create ports
  set clk_0 [ create_bd_port -dir I -type clk clk_0 ]
  set cout [ create_bd_port -dir O -from 0 -to 0 cout ]
  set sum [ create_bd_port -dir O -from 0 -to 0 sum ]

  # Create instance: si_1, and set properties
  set si_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 si_1 ]
  set_property -dict [ list \
   CONFIG.C_SIZE {1} \
 ] $si_1

  # Create instance: si_2, and set properties
  set si_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 si_2 ]
  set_property -dict [ list \
   CONFIG.C_SIZE {1} \
 ] $si_2

  # Create instance: si_3, and set properties
  set si_3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 si_3 ]
  set_property -dict [ list \
   CONFIG.C_OPERATION {or} \
   CONFIG.C_SIZE {1} \
   CONFIG.LOGO_FILE {data/sym_orgate.png} \
 ] $si_3

  # Create instance: vio_0, and set properties
  set vio_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:vio:3.0 vio_0 ]
  set_property -dict [ list \
   CONFIG.C_NUM_PROBE_IN {2} \
   CONFIG.C_NUM_PROBE_OUT {3} \
 ] $vio_0

  # Create instance: xor_0, and set properties
  set xor_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 xor_0 ]
  set_property -dict [ list \
   CONFIG.C_OPERATION {xor} \
   CONFIG.C_SIZE {1} \
   CONFIG.LOGO_FILE {data/sym_xorgate.png} \
 ] $xor_0

  # Create instance: xor_1, and set properties
  set xor_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 xor_1 ]
  set_property -dict [ list \
   CONFIG.C_OPERATION {xor} \
   CONFIG.C_SIZE {1} \
   CONFIG.LOGO_FILE {data/sym_xorgate.png} \
 ] $xor_1

  # Create port connections
  connect_bd_net -net Op1_0_1 [get_bd_pins si_1/Op1] [get_bd_pins vio_0/probe_out0] [get_bd_pins xor_0/Op1]
  connect_bd_net -net Op2_0_1 [get_bd_pins si_1/Op2] [get_bd_pins vio_0/probe_out1] [get_bd_pins xor_0/Op2]
  connect_bd_net -net Op2_1_1 [get_bd_pins si_2/Op2] [get_bd_pins vio_0/probe_out2] [get_bd_pins xor_1/Op2]
  connect_bd_net -net clk_0_1 [get_bd_ports clk_0] [get_bd_pins vio_0/clk]
  connect_bd_net -net si_1_Res [get_bd_pins si_1/Res] [get_bd_pins si_3/Op1]
  connect_bd_net -net si_2_Res [get_bd_pins si_2/Res] [get_bd_pins si_3/Op2]
  connect_bd_net -net si_3_Res [get_bd_ports cout] [get_bd_pins si_3/Res] [get_bd_pins vio_0/probe_in1]
  connect_bd_net -net xor_0_Res [get_bd_pins si_2/Op1] [get_bd_pins xor_0/Res] [get_bd_pins xor_1/Op1]
  connect_bd_net -net xor_1_Res [get_bd_ports sum] [get_bd_pins vio_0/probe_in0] [get_bd_pins xor_1/Res]

  # Create address segments


  # Restore current instance
  current_bd_instance $oldCurInst

  validate_bd_design
  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


