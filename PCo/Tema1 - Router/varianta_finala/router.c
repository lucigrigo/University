/*
                    Protocoale de Comunicatii
	                    Tema 1 - Router
                    Grigore Lucian-Florin 324CD
*/
#include "skel.h"
#include <netinet/if_ether.h>
#include <queue.h>

// structure that describes one entry in the arp table
struct arp_entry {
  uint8_t *h_addr;      // physical address
  uint8_t *p_addr;      // ip address
  uint32_t search_addr; // conversion of ip address used for searching
  int interface;        // interface
};

// structure that describes one entry in the routing table
struct route_entry {
  uint32_t preffix;  // preffix
  uint32_t next_hop; // next hop
  uint32_t mask;     // mask
  int interface;     // interface
};

// structure that describes a node used in trie for the routing table
struct route_node {
  struct route_node *left;      // left child
  struct route_node *right;     // right child
  int is_leaf;                  // indicates if it is a leaf or not
  int size;                     // number of arp entries that it has
  struct route_entry **entries; // number of entries
};

// structure that describes a node used in trie for the routing table
struct node {
  struct node *left;       // left child
  struct node *right;      // right child
  int is_leaf;             // indicates if it is a leaf
  struct arp_entry *entry; // corresponding arp entry
};

// structure that describes one entry in the list used to store packets on hold
struct p_db {
  packet *p;         // corresponding packet
  struct p_db *next; // pointer to the next entry
};

// function that created one entry in the queue of packets from a given packet
struct p_db *create_p_db(packet *pck) {
  // pentru memorarea pachetului, il copiez intr-o noua zona de memorie
  struct p_db *n = (struct p_db *)malloc(sizeof(struct p_db));
  packet *new_p = (packet *)malloc(sizeof(packet));
  memcpy(new_p, pck, sizeof(packet));
  n->p = new_p;
  n->next = NULL;
  return n;
}

// function that adds one more entry to the list of packets
struct p_db *add_to_q(struct p_db *first, packet *p) {
  if (first == NULL) {
    // there are no packets on hold yet
    return create_p_db(p);
  }
  // finding the last entry
  struct p_db *temp = first;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  // putting new entry to the tail
  temp->next = create_p_db(p);
  return first;
}

// function used by qsort for the entries in the same node of the routing table
int rtable_mask_comparator(const void *p, const void *q) {
  // sorting descending by the mask
  return (*(struct route_entry **)q)->mask - (*(struct route_entry **)p)->mask;
}

// function that creates a new entry in the routing tree
struct route_entry *create_route_entry(uint32_t preffix, uint32_t next_hop,
                                       uint32_t mask, int interface) {
  struct route_entry *e =
      (struct route_entry *)malloc(sizeof(struct route_entry));
  e->preffix = preffix;
  e->next_hop = next_hop;
  e->mask = mask;
  e->interface = interface;
  return e;
}

// function that adds a new routing entry to a single node
void add_entry_to_node(struct route_node *node, struct route_entry *entry) {
  node->entries[node->size] = entry;
  node->size = node->size + 1;
  // entries of the same node are kept in descending order by mask
  qsort(node->entries, node->size, sizeof(struct route_entry *),
        rtable_mask_comparator);
}

// function that creates a new trie node for the routing tree
struct route_node *create_route_node(struct route_entry *entry) {
  struct route_node *n = (struct route_node *)malloc(sizeof(struct route_node));
  n->entries = (struct route_entry **)malloc(100 * sizeof(struct route_node *));
  n->left = NULL;
  n->right = NULL;
  n->is_leaf = 1;
  n->size = 1;
  n->entries[0] = entry;
  return n;
}

// function that creates a new empty node for the routing tree
struct route_node *create_empty_route_node() {
  struct route_node *n = (struct route_node *)malloc(sizeof(struct route_node));
  n->left = NULL;
  n->right = NULL;
  n->entries = NULL;
  n->is_leaf = 0;
  n->size = 0;
  return n;
}

// function that creates a new empty node for the arp routing tree
struct node *createEmptyNode() {
  struct node *n = (struct node *)malloc(sizeof(struct node));
  n->left = NULL;
  n->right = NULL;
  n->entry = NULL;
  n->is_leaf = 0;
  return n;
}

// function that creates a new node with a given arp entry for the arp routing
// tree
struct node *createArpNode(struct arp_entry *a) {
  struct node *n = (struct node *)malloc(sizeof(struct node));
  n->left = NULL;
  n->right = NULL;
  n->is_leaf = 1;
  n->entry = a;
  return n;
}

// function that creates a new arp entry
struct arp_entry *createEntry(uint8_t spa[4], uint8_t sha[6], int interface,
                              uint32_t search_addr) {
  struct arp_entry *e = (struct arp_entry *)malloc(sizeof(struct arp_entry));
  e->interface = interface;
  // keeping mac and ip addreses in a new memory location
  e->h_addr = (uint8_t *)malloc(sizeof(uint8_t) * 6);
  e->p_addr = (uint8_t *)malloc(sizeof(uint8_t) * 4);
  e->p_addr[0] = spa[0];
  e->p_addr[1] = spa[1];
  e->p_addr[2] = spa[2];
  e->p_addr[3] = spa[3];
  e->h_addr[0] = sha[0];
  e->h_addr[1] = sha[1];
  e->h_addr[2] = sha[2];
  e->h_addr[3] = sha[3];
  e->h_addr[4] = sha[4];
  e->h_addr[5] = sha[5];
  e->search_addr = search_addr;
  return e;
}

// function that creates a new node in the routing tree from a given array of
// already existent entries
struct route_node *
create_route_node_with_entries(struct route_entry *carry_entries[],
                               int carry_size) {
  struct route_node *n = (struct route_node *)malloc(sizeof(struct route_node));
  n->entries = (struct route_entry **)malloc(100 * sizeof(struct route_node *));
  n->size = carry_size;
  n->is_leaf = 1;
  n->left = NULL;
  n->right = NULL;
  int i;
  for (i = 0; i < carry_size; i++) {
    n->entries[i] = carry_entries[i];
  }
  return n;
}

// function that searches for a given address in the routing tree
struct route_entry *search_route_entry(struct route_node *root, uint32_t addr) {
  if (root == NULL) {
    // tree is empty
    return NULL;
  }

  // traversing the tree
  struct route_node *current_node = root;
  // starting from the first bit in the left
  int poz = 32;

  // looking for a NULL node or one that is a leaf (has a correponding entry)
  while (current_node != NULL && current_node->is_leaf != 1) {
    // comparing current position
    int compare_bit = ((1 << poz) & (addr & current_node->entries[0]->mask));

    // going left or right based on current comparation
    if (compare_bit != 0) {
      current_node = current_node->right;
    } else {
      current_node = current_node->left;
    }

    // highly unlikely error while searching for an address
    if (poz == 0) {
      perror("rtable search error!\n");
      exit(4);
    }
    // comparing next bit
    poz--;
  }

  // if the node is empty or has no entries
  if (current_node == NULL || current_node->entries == NULL) {
    return NULL;
  }

  // returning the entry with the biggest mask
  return current_node->entries[0];
}

// function that inserts a new routing entry to the routing tree
struct route_node *insert_route_entry(struct route_node *root,
                                      struct route_entry *new_entry) {
  if (root == NULL) {
    // if it is the first node of the tree
    return create_route_node(new_entry);
  }

  int has_carry = 0;
  int carry_size = 0;
  struct route_entry **carry_entries;
  struct route_node *current_node = root;
  int poz = 32;

  while (1) {
    // if the current insert carries no partially matched entries
    if (has_carry == 0) {
      // if the current node has entries
      if (current_node->size != 0) {
        // we carry them through the process
        carry_entries = current_node->entries;
        current_node->is_leaf = 0;
        carry_size = current_node->size;
        current_node->size = 0;
        has_carry = 1;
        continue;
      }
      // comparing by the current bit of the preffix
      int bit = ((1 << poz) & new_entry->preffix);

      // going to the right
      if (bit != 0) {
        if (current_node->right == NULL) {
          // putting new node in this position
          current_node->right = create_route_node(new_entry);
          break;
        } else {
          // continue traversing
          current_node = current_node->right;
        }
        // going to the left
      } else {
        if (current_node->left == NULL) {
          // putting new node in this position
          current_node->left = create_route_node(new_entry);
          break;
        } else {
          // continue traversing
          current_node = current_node->left;
        }
      }
    } else {
      // if the preffix of the carries is equal to the new one
      if (carry_entries[0]->preffix == new_entry->preffix) {
        // adding them to the current node
        current_node =
            create_route_node_with_entries(carry_entries, carry_size);
        add_entry_to_node(current_node, new_entry);
        break;
      }
      // comparing by the current bit in the preffix
      int carry_addr = ((1 << poz) & carry_entries[0]->preffix);
      int new_addr = ((1 << poz) & new_entry->preffix);

      // if the current bit is the same
      if (carry_addr == new_addr) {
        // keep traversing to the right node
        if (carry_addr != 0) {
          current_node->right = create_empty_route_node();
          current_node = current_node->right;
        } else {
          // keep traversing to the left node
          current_node->left = create_empty_route_node();
          current_node = current_node->left;
        }
        // if they are different
      } else {
        // we create new nodes to correspond to the new and carry entry
        struct route_node *carry_route_node =
            create_route_node_with_entries(carry_entries, carry_size);
        struct route_node *new_route_node = create_route_node(new_entry);

        // finding which to put on the left and which on the right
        if (carry_addr != 0) {
          current_node->right = carry_route_node;
          current_node->left = new_route_node;
          break;
        } else {
          current_node->right = new_route_node;
          current_node->left = carry_route_node;
          break;
        }
      }
    }

    // highly unlikely insertion error
    if (poz == 0) {
      perror("rtable insert error!\n");
      exit(3);
    }
    // continue comparing to the next position
    poz--;
  }

  return root;
}

//
// int comp(struct arp_entry *node_entry, struct arp_entry *searched_entry) {
//   int i;
//   for (i = 3; i >= 0; --i) {
//     if (node_entry->p_addr[i] != searched_entry->p_addr[i]) {
//       return 0;
//     }
//   }
//   return 1;
// }

// function that searches for a given entry in the arp routing tree
struct arp_entry *searchEntry(struct node *root, struct arp_entry *entry) {
  if (root == NULL) {
    // if the tree is empty
    return NULL;
  }
  // starting traversing
  struct node *current_node = root;
  // starting comparing from the first bit from the left
  int poz = 32;

  // keep traversing as long as we don't reach a dead end or a leaf with entry
  while (current_node != NULL && current_node->is_leaf != 1) {
    // current step comparison bit
    int compare_bit = ((1 << poz) & entry->search_addr);

    // if the current node has the address we are looking for
    if (current_node != NULL && current_node->entry != NULL &&
        current_node->entry->search_addr == entry->search_addr) {
      return current_node->entry;
    }

    if (compare_bit != 0) {
      // traversing to the right
      current_node = current_node->right;
    } else {
      // traversing to the left
      current_node = current_node->left;
    }

    // continue comparing to the next bit
    poz--;
  }

  // no address found
  if (current_node == NULL) {
    return NULL;
  }

  // we found a leaf with the searched address
  if (entry->search_addr == current_node->entry->search_addr) {
    return current_node->entry;
  }

  // this should be the point where we update information about the entry
  // but it's not the point of this program
  return NULL;
}

// function that inserts a new arp entry in the arp routing tree
struct node *insertNode(struct node *root, struct arp_entry *new_entry) {
  if (root == NULL) {
    // the tree was empty
    root = createArpNode(new_entry);
    return root;
  }

  int poz = 32;
  struct arp_entry *carry_entry = NULL;
  struct node *current_node = root;
  struct node *parent_node = NULL;

  // starting traversing the tree
  while (1) {
    // if the node carries no other entry with it
    if (carry_entry == NULL) {
      // if the current node has an entry
      if (current_node->entry != NULL) {
        carry_entry = current_node->entry;
        current_node->entry = NULL;
        current_node->is_leaf = 0;
        continue;
      }

      parent_node = current_node;
      // current comparison bit
      int bit = ((1 << poz) & new_entry->search_addr);

      // if we should go to the right
      if (bit != 0) {
        if (parent_node->right == NULL) {
          // creating a new node in an empty place
          parent_node->right = createArpNode(new_entry);
          break;
        } else {
          // keep traversing
          current_node = parent_node->right;
        }
        // if we should go to the left
      } else {
        if (parent_node->left == NULL) {
          // creating a new node in an empty place
          parent_node->left = createArpNode(new_entry);
          break;
        } else {
          // keep traversing
          current_node = parent_node->left;
        }
      }
      // the current insertion carries an aditional entry
    } else {
      // if the carry entry address is the same with the new one
      if (carry_entry->search_addr == new_entry->search_addr) {
        break;
      }

      // current position comparison values
      int carry_addr = ((1 << poz) & carry_entry->search_addr);
      int new_addr = ((1 << poz) & new_entry->search_addr);

      // if the values are the same, we keep traversing
      if (carry_addr == new_addr) {
        parent_node = current_node;
        // to the right
        if (carry_addr != 0) {
          parent_node->right = createEmptyNode();
          current_node = parent_node->right;
        } else { // to the left
          parent_node->left = createEmptyNode();
          current_node = parent_node->left;
        }
        // if they are different
      } else {
        // we create new nodes
        struct node *carry_node = createArpNode(carry_entry);
        struct node *new_node = createArpNode(new_entry);

        // deciding which of the nodes to put where
        if (carry_addr != 0) {
          current_node->right = carry_node;
          current_node->left = new_node;
        } else {
          current_node->right = new_node;
          current_node->left = carry_node;
        }
        break;
      }
    }

    // continue comparing to the next bit
    poz--;
  }

  // returning new tree
  return root;
}

// function used to convert from uint32 to u_char *
void convert(struct ether_arp *ether_arp_hdr, unsigned int addr) {
  int i;
  for (i = 0; i < 4; ++i) {
    memcpy((ether_arp_hdr->arp_spa + i), (char *)&addr + i, 1);
  }
}

// function used to convert from u_char * to uint32
uint32_t convert_to_addr(u_char *src, int len) {
  int i;
  uint32_t n = 0;
  for (i = 0; i < len; i++) {
    n += (uint32_t)(src[i]) << (8 * i);
    // printf("%d\n", (uint32_t)(src[i]));
  }
  return n;
}

// uint32_t convert_to_addr2(u_char *src, int len) {
//   int i;
//   uint32_t n = 0;
//   for (i = 0; i < len; i++) {
//     n += (uint32_t)(src[i]) << (8 * (len - i - 1));
//   }
//   return n;
// }

// void convert2(struct ether_arp *ether_arp_hdr, unsigned int t_addr) {
//   int i;
//   for (i = 0; i < 4; ++i) {
//     memcpy((ether_arp_hdr->arp_tpa + i), (char *)&t_addr + i, 1);
//   }
// }

// function used to compute checksum (taken from lab04)
uint16_t ip_checksum(void *vdata, size_t length) {
  char *data = (char *)vdata;
  uint64_t acc = 0xffff;

  unsigned int offset = ((uintptr_t)data) & 3;
  if (offset) {
    size_t count = 4 - offset;
    if (count > length)
      count = length;
    uint32_t word = 0;
    memcpy(offset + (char *)&word, data, count);
    acc += ntohl(word);
    data += count;
    length -= count;
  }

  char *data_end = data + (length & ~3);
  while (data != data_end) {
    uint32_t word;
    memcpy(&word, data, 4);
    acc += ntohl(word);
    data += 4;
  }
  length &= 3;

  if (length) {
    uint32_t word = 0;
    memcpy(&word, data, length);
    acc += ntohl(word);
  }

  acc = (acc & 0xffffffff) + (acc >> 32);
  while (acc >> 16) {
    acc = (acc & 0xffff) + (acc >> 16);
  }

  if (offset & 1) {
    acc = ((acc & 0xff00) >> 8) | ((acc & 0x00ff) << 8);
  }

  return htons(~acc);
}

// function that sends an arp reply after receiving an arp request
void send_arp_reply(struct queue *q, struct arp_entry *sender,
                    struct ether_arp *ether_arp_hdr, packet *p,
                    struct route_node *route_root,
                    struct ether_header *eth_hdr) {
  // ethernet header
  // destination mac
  eth_hdr->ether_dhost[0] = eth_hdr->ether_shost[0];
  eth_hdr->ether_dhost[1] = eth_hdr->ether_shost[1];
  eth_hdr->ether_dhost[2] = eth_hdr->ether_shost[2];
  eth_hdr->ether_dhost[3] = eth_hdr->ether_shost[3];
  eth_hdr->ether_dhost[4] = eth_hdr->ether_shost[4];
  eth_hdr->ether_dhost[5] = eth_hdr->ether_shost[5];

  // source mac
  get_interface_mac(p->interface, eth_hdr->ether_shost);

  // arp header
  // target hardware address
  ether_arp_hdr->arp_tha[0] = ether_arp_hdr->arp_sha[0];
  ether_arp_hdr->arp_tha[1] = ether_arp_hdr->arp_sha[1];
  ether_arp_hdr->arp_tha[2] = ether_arp_hdr->arp_sha[2];
  ether_arp_hdr->arp_tha[3] = ether_arp_hdr->arp_sha[3];
  ether_arp_hdr->arp_tha[4] = ether_arp_hdr->arp_sha[4];
  ether_arp_hdr->arp_tha[5] = ether_arp_hdr->arp_sha[5];

  // target protocol address
  ether_arp_hdr->arp_tpa[0] = ether_arp_hdr->arp_spa[0];
  ether_arp_hdr->arp_tpa[1] = ether_arp_hdr->arp_spa[1];
  ether_arp_hdr->arp_tpa[2] = ether_arp_hdr->arp_spa[2];
  ether_arp_hdr->arp_tpa[3] = ether_arp_hdr->arp_spa[3];

  // source protocol address
  struct in_addr addr;
  inet_aton(get_interface_ip(p->interface), &addr);
  unsigned int addr_no = addr.s_addr;
  convert(ether_arp_hdr, addr_no);

  // source hardware address
  get_interface_mac(p->interface, ether_arp_hdr->arp_sha);

  // setting package type
  ether_arp_hdr->ea_hdr.ar_op = htons(ARPOP_REPLY);

  // setting package length
  p->len = sizeof(struct ether_header) + sizeof(struct ether_arp);

  // setting interface
  uint32_t search_addr = convert_to_addr(ether_arp_hdr->arp_tpa, 4);
  struct route_entry *searched_entry =
      search_route_entry(route_root, search_addr);

  // sending packet
  int confirm_sent = send_packet(p->interface, p);
  if (confirm_sent == 0) {
    perror("arp reply not sent!\n");
    exit(1);
  }
}

// function that responds to an arp reply and searches the packets on hold to
// check if one of those needs to be forwarded now to the new address
struct p_db *respond_to_arp_reply(struct queue *q,
                                  struct ether_arp *ether_arp_hdr, packet *p,
                                  struct p_db *queued_packets) {
  if (queued_packets == NULL) {
    // no packets on hold
    return queued_packets;
  }

  // computing source address value of the received packet, used for search
  struct p_db *p_search = NULL;
  struct p_db *search = queued_packets;
  uint32_t daddr = convert_to_addr(
      (((struct ether_arp *)(p->payload + sizeof(struct ether_header)))
           ->arp_spa),
      4);

  // iterating through the packets
  while (search != NULL) {
    if (search->p == NULL) // highly unlikely error check
      continue;
    packet *pkt = search->p;
    struct iphdr *ip_hdr =
        (struct iphdr *)(pkt->payload + sizeof(struct ether_header));

    if (daddr == ip_hdr->daddr) {
      // a packet on hold that needs to be sent is found
      // ethernet header
      struct ether_header *eth_hdr = (struct ether_header *)pkt->payload;

      // sender mac
      get_interface_mac(p->interface, eth_hdr->ether_shost);

      struct ether_arp *eth_arp_hdr =
          (struct ether_arp *)(p->payload + sizeof(struct ether_header));
      // target mac
      eth_hdr->ether_dhost[0] = eth_arp_hdr->arp_sha[0];
      eth_hdr->ether_dhost[1] = eth_arp_hdr->arp_sha[1];
      eth_hdr->ether_dhost[2] = eth_arp_hdr->arp_sha[2];
      eth_hdr->ether_dhost[3] = eth_arp_hdr->arp_sha[3];
      eth_hdr->ether_dhost[4] = eth_arp_hdr->arp_sha[4];
      eth_hdr->ether_dhost[5] = eth_arp_hdr->arp_sha[5];

      // adjusting ttl and checksum
      ip_hdr->ttl = ip_hdr->ttl - 1;
      ip_hdr->check = 0;
      ip_hdr->check = ip_checksum(ip_hdr, sizeof(struct iphdr));

      // sending packet
      int confirmation_sent = send_packet(p->interface, pkt);
      if (confirmation_sent < 0) {
        perror("error sending packet\nquiting...\n");
        exit(2);
      }

      // free memory space
      free(search->p);
      if (p_search != NULL) {
        // eliminating sent packet
        p_search->next = search->next;
        search = search->next;
        continue;
      } else {
        // it was the only packet on hold
        return NULL;
      }
    }

    // keep iterating
    p_search = search;
    search = search->next;
  }

  // return new packet list
  return queued_packets;
}

// function used to decide the type of the received ip packet
int check_ip_packet(packet p) {
  struct icmphdr *icmp_hdr =
      (struct icmphdr *)(p.payload + sizeof(struct ether_header) +
                         sizeof(struct iphdr));
  struct iphdr *ip_hdr =
      (struct iphdr *)(p.payload + sizeof(struct ether_header));

  // getting the corresponding address to that interface
  struct in_addr own_addr;
  inet_aton(get_interface_ip(p.interface), &own_addr);

  // checking to see if the received packet is sent to the router and
  // it is ICMP ECHO
  if ((ip_hdr->protocol == IPPROTO_ICMP) &&
      (icmp_hdr->type == 8 || icmp_hdr->type == 0) &&
      (ip_hdr->daddr == own_addr.s_addr)) {
    return 1;

  } else if (ip_hdr->daddr == own_addr.s_addr) {
    // is sent to the router, but it is not ICMP ECHO
    return 0;
  }

  // the packet will follow the normal forwarding process
  return 2;
}

// function to reply to ICMP ECHO with ICMP ECHO REPLY
void reply_icmp_echo(packet *p) {
  struct iphdr *ip_hdr =
      (struct iphdr *)(p->payload + sizeof(struct ether_header));

  // ethernet header setup
  struct ether_header *eth_hdr = (struct ether_header *)p->payload;
  uint8_t *temp = eth_hdr->ether_dhost;
  eth_hdr->ether_dhost[0] = eth_hdr->ether_shost[0];
  eth_hdr->ether_dhost[1] = eth_hdr->ether_shost[1];
  eth_hdr->ether_dhost[2] = eth_hdr->ether_shost[2];
  eth_hdr->ether_dhost[3] = eth_hdr->ether_shost[3];
  eth_hdr->ether_dhost[4] = eth_hdr->ether_shost[4];
  eth_hdr->ether_dhost[5] = eth_hdr->ether_shost[5];
  eth_hdr->ether_shost[0] = temp[0];
  eth_hdr->ether_shost[1] = temp[1];
  eth_hdr->ether_shost[2] = temp[2];
  eth_hdr->ether_shost[3] = temp[3];
  eth_hdr->ether_shost[4] = temp[4];
  eth_hdr->ether_shost[5] = temp[5];

  // ip header setup
  uint32_t temp_addr = ip_hdr->saddr;
  ip_hdr->saddr = ip_hdr->daddr;
  ip_hdr->daddr = temp_addr;
  ip_hdr->ttl = ip_hdr->ttl - 1;
  ip_hdr->check = 0;
  ip_hdr->check = ip_checksum(ip_hdr, sizeof(struct iphdr));

  // icmp header setup
  struct icmphdr *icmp_hdr =
      (struct icmphdr *)(p->payload + sizeof(struct ether_header) +
                         sizeof(struct iphdr));
  icmp_hdr->type = (uint8_t)ICMP_ECHOREPLY;

  // sending packet
  int confirmation_sent = send_packet(p->interface, p);
  if (confirmation_sent < 0) {
    perror("error sending icmp echo reply...\nquiting...\n");
    exit(1);
  }
}

// function that forwards a received packet to already known address
void forward_packet(packet *p, struct arp_entry *dest) {
  // setting ethernet header
  struct ether_header *eth_hdr = (struct ether_header *)p->payload;
  get_interface_mac(dest->interface, eth_hdr->ether_shost);
  eth_hdr->ether_dhost[0] = dest->h_addr[0];
  eth_hdr->ether_dhost[1] = dest->h_addr[1];
  eth_hdr->ether_dhost[2] = dest->h_addr[2];
  eth_hdr->ether_dhost[3] = dest->h_addr[3];
  eth_hdr->ether_dhost[4] = dest->h_addr[4];
  eth_hdr->ether_dhost[5] = dest->h_addr[5];

  // adjusting ttl and checksum in ip header
  struct iphdr *ip_hdr =
      (struct iphdr *)(p->payload + sizeof(struct ether_header));
  ip_hdr->ttl = ip_hdr->ttl - 1;
  ip_hdr->check = 0;
  ip_hdr->check = ip_checksum(ip_hdr, sizeof(struct iphdr));

  // sending packet
  int confirmation_sent = send_packet(dest->interface, p);
  if (confirmation_sent < 0) {
    perror("error forwarding packet\nquiting...\n");
    exit(2);
  }
}

// function that replies with DESTINATION UNREACHABLE
void reply_dest_unreach(packet *p) {
  // setting header pointers
  struct icmphdr *icmp_hdr =
      (struct icmphdr *)(p->payload + sizeof(struct ether_header) +
                         sizeof(struct iphdr));
  struct ether_header *eth_hdr = (struct ether_header *)p->payload;
  struct iphdr *ip_hdr =
      (struct iphdr *)(p->payload + sizeof(struct ether_header));

  // copying into data
  memcpy(p->payload + sizeof(struct ether_header) + sizeof(struct iphdr) +
             sizeof(struct icmphdr),
         ip_hdr, sizeof(struct iphdr) + 64);

  // setting package length
  p->len = sizeof(struct ether_header) + sizeof(struct iphdr) * 2 +
           sizeof(struct icmphdr) + 64;

  // setting icmp header
  icmp_hdr->type = (uint8_t)ICMP_DEST_UNREACH;
  icmp_hdr->code = (uint8_t)0;
  icmp_hdr->checksum = 0;
  icmp_hdr->checksum = ip_checksum(
      icmp_hdr, p->len - sizeof(struct ether_header) - sizeof(struct iphdr));

  // setting ip header
  uint32_t temp_addr = ip_hdr->daddr;
  ip_hdr->daddr = ip_hdr->saddr;
  ip_hdr->saddr = temp_addr;
  ip_hdr->ttl = (uint8_t)64;
  ip_hdr->frag_off = (uint16_t)0;
  ip_hdr->protocol = (uint8_t)IPPROTO_ICMP;
  ip_hdr->id = ip_hdr->id + 1;
  ip_hdr->tot_len = htons(ntohs(ip_hdr->tot_len) + sizeof(struct iphdr) +
                          sizeof(struct icmphdr));
  ip_hdr->check = 0;
  ip_hdr->check = ip_checksum(ip_hdr, sizeof(struct iphdr));

  // setting ethernet header
  eth_hdr->ether_dhost[0] = eth_hdr->ether_shost[0];
  eth_hdr->ether_dhost[1] = eth_hdr->ether_shost[1];
  eth_hdr->ether_dhost[2] = eth_hdr->ether_shost[2];
  eth_hdr->ether_dhost[3] = eth_hdr->ether_shost[3];
  eth_hdr->ether_dhost[4] = eth_hdr->ether_shost[4];
  eth_hdr->ether_dhost[5] = eth_hdr->ether_shost[5];
  get_interface_mac(p->interface, eth_hdr->ether_shost);

  // sending packet
  int confirmation_sent = send_packet(p->interface, p);
  if (confirmation_sent < 0) {
    perror("error sending host unreachable\nquiting...\n");
    exit(2);
  }
}

// function that replies with TIME EXCEEDED
void reply_icmp_timeout(packet *p) {
  // setting header pointers
  struct icmphdr *icmp_hdr =
      (struct icmphdr *)(p->payload + sizeof(struct ether_header) +
                         sizeof(struct iphdr));
  struct ether_header *eth_hdr = (struct ether_header *)p->payload;
  struct iphdr *ip_hdr =
      (struct iphdr *)(p->payload + sizeof(struct ether_header));

  // copying into data
  memcpy(p->payload + sizeof(struct ether_header) + sizeof(struct iphdr) +
             sizeof(struct icmphdr),
         ip_hdr, sizeof(struct iphdr) + 64);

  // setting package length
  p->len = sizeof(struct ether_header) + sizeof(struct iphdr) * 2 +
           sizeof(struct icmphdr) + 64;

  // setting icmp header
  icmp_hdr->type = (uint8_t)ICMP_TIME_EXCEEDED;
  icmp_hdr->code = (uint8_t)0;
  icmp_hdr->checksum = 0;
  icmp_hdr->checksum = ip_checksum(
      icmp_hdr, p->len - sizeof(struct ether_header) - sizeof(struct iphdr));

  // setting ip header
  uint32_t temp_addr = ip_hdr->daddr;
  ip_hdr->daddr = ip_hdr->saddr;
  ip_hdr->saddr = temp_addr;
  ip_hdr->ttl = (uint8_t)64;
  ip_hdr->frag_off = (uint16_t)0;
  ip_hdr->protocol = (uint8_t)IPPROTO_ICMP;
  ip_hdr->id = ip_hdr->id + 1;
  ip_hdr->tot_len = htons(ntohs(ip_hdr->tot_len) + sizeof(struct iphdr) +
                          sizeof(struct icmphdr));
  ip_hdr->check = 0;
  ip_hdr->check = ip_checksum(ip_hdr, sizeof(struct iphdr));

  // setting ethernet header
  eth_hdr->ether_dhost[0] = eth_hdr->ether_shost[0];
  eth_hdr->ether_dhost[1] = eth_hdr->ether_shost[1];
  eth_hdr->ether_dhost[2] = eth_hdr->ether_shost[2];
  eth_hdr->ether_dhost[3] = eth_hdr->ether_shost[3];
  eth_hdr->ether_dhost[4] = eth_hdr->ether_shost[4];
  eth_hdr->ether_dhost[5] = eth_hdr->ether_shost[5];
  get_interface_mac(p->interface, eth_hdr->ether_shost);

  // sending packet
  int confirmation_sent = send_packet(p->interface, p);
  if (confirmation_sent < 0) {
    perror("error sending timeout\nquiting...\n");
    exit(2);
  }
}

// function that sends arp request to acquire a new mac address
void send_arp_request(packet *p, int d_interface) {
  // setting ip header pointer
  struct iphdr *ip_hdr =
      (struct iphdr *)(p->payload + sizeof(struct ether_header));

  // creating packet
  packet pkt;
  pkt.interface = d_interface;

  // creating new headers
  struct arphdr new_arphdr;
  struct ether_arp new_ether_arp;
  struct ether_header new_ether_header;

  // ethernet header setup
  new_ether_header.ether_type = htons(ETHERTYPE_ARP);
  get_interface_mac(d_interface, new_ether_header.ether_shost);
  hwaddr_aton("ff:ff:ff:ff:ff:ff", new_ether_header.ether_dhost);

  // arp ethernet header setup
  // -- arp_sha
  get_interface_mac(d_interface, new_ether_arp.arp_sha);
  // -- arp_spa
  struct in_addr addr;
  inet_aton(get_interface_ip(d_interface), &addr);
  unsigned int addr_no = addr.s_addr;
  convert(&new_ether_arp, addr_no);
  // -- arp_tha
  hwaddr_aton("ff:ff:ff:ff:ff:ff", new_ether_arp.arp_tha);
  // -- arp_tpa;
  convert2(&new_ether_arp, ip_hdr->daddr);

  // arp header setup
  new_arphdr.ar_hrd = htons(ARPHRD_ETHER);
  new_arphdr.ar_pro = htons(0x0800);
  new_arphdr.ar_hln = (uint8_t)6;
  new_arphdr.ar_pln = (uint8_t)4;
  new_arphdr.ar_op = htons(ARPOP_REQUEST);

  // moving new built headers into payload
  memcpy(pkt.payload, &new_ether_header, sizeof(struct ether_header));
  memcpy(pkt.payload + sizeof(struct ether_header), &new_ether_arp,
         sizeof(struct ether_arp));
  memcpy(pkt.payload + sizeof(struct ether_header), &new_arphdr,
         sizeof(struct arphdr));

  // setting package length
  pkt.len = sizeof(struct ether_header) + sizeof(struct ether_arp);

  // sending packet
  int confirmation_sent = send_packet(pkt.interface, &pkt);
  if (confirmation_sent < 0) {
    perror("arp request sending error\nquiting...\n");
    exit(2);
  }
}

// function that deals with the forwarding packet with and ip packet
struct p_db *reply_icmp(queue *q, packet *p, struct route_node *rtable_root,
                        struct node *arptable_root,
                        struct p_db *queued_packets) {
  // seting ip header pinter
  struct iphdr *ip_hdr =
      (struct iphdr *)(p->payload + sizeof(struct ether_header));

  // get destination ip
  uint32_t dest_addr = ip_hdr->daddr;

  // check checksum
  if (ip_checksum(ip_hdr, sizeof(struct iphdr))) {
    // if the checksum is wrong we drop the packet
    perror("checksum error\ndropping packet...\n");
    return queued_packets;
  }

  // checking time to live
  if (ip_hdr->ttl <= 1) {
    // sending time exceeded error back
    perror("timeout ttl\nsending error back...\n");
    reply_icmp_timeout(p);
    return queued_packets;
  }

  // finding interface in rtable
  struct route_entry *search_entry = search_route_entry(rtable_root, dest_addr);
  if (search_entry == NULL) {
    // sending destination unreachable error back
    reply_dest_unreach(p);
    printf("dest unreacheable\nsending icmp packet back...\n");
    return queued_packets;
  }

  // check to see if we have the requested arp entry in our table
  struct arp_entry *e = (struct arp_entry *)malloc(sizeof(struct arp_entry));
  e->interface = search_entry->interface;
  e->search_addr = ip_hdr->daddr;
  struct arp_entry *search_arp_entry = searchEntry(arptable_root, e);

  // not matching arp entry found
  if (search_arp_entry == NULL) {
    // send arp request to get next hardware address
    send_arp_request(p, search_entry->interface);
    // queue current packet
    queued_packets = add_to_q(queued_packets, p);
  } else {
    // forwarding packet to already known address
    forward_packet(p, search_arp_entry);
  }

  return queued_packets;
}

// function that parses the routing table
struct route_node *parse_rtable(struct route_node *root) {
  FILE *ffile = fopen("rtable.txt", "r");

  // variable used for parsing
  uint32_t in_preffix = -1;
  uint32_t in_next_hop = -1;
  uint32_t in_mask = -1;
  int in_interface = -1;

  // additional variables used in the process
  size_t buffer_size = 128;
  char *buffer = (char *)malloc(buffer_size);
  const char delimiter[2] = " ";
  struct in_addr temp;
  char *split_buffer;
  int nread;

  // reading all lines in the input file
  while ((nread = getline(&buffer, &buffer_size, ffile)) != -1) {
    // getting preffix
    split_buffer = strtok(buffer, delimiter);
    inet_aton(split_buffer, &temp);
    in_preffix = temp.s_addr;

    // getting next hop
    split_buffer = strtok(NULL, delimiter);
    inet_aton(split_buffer, &temp);
    in_next_hop = temp.s_addr;

    // getting mask
    split_buffer = strtok(NULL, delimiter);
    inet_aton(split_buffer, &temp);
    in_mask = temp.s_addr;

    // getting interface
    split_buffer = strtok(NULL, delimiter);
    in_interface = atoi(split_buffer);

    // highly unlikely input error (empty file)
    if (in_interface == -1) {
      perror("rtable insert error\nquiting...\n");
      exit(1);
    }

    // creating and inserting new entry in the tree
    struct route_entry *new_route_entry =
        create_route_entry(in_preffix, in_next_hop, in_mask, in_interface);
    root = insert_route_entry(root, new_route_entry);
  }

  // closing input file
  fclose(ffile);

  return root;
}

// main function of the program
int main(int argc, char *argv[]) {
  // setvbuf(stdout, NULL, _IONBF, 0);
  packet received_packet;
  int rc;
  // queue packet_q;
  // packet_q = queue_create();
  struct node *root = NULL;                 // root for the arp routing tree
  struct route_node *rtable_root = NULL;    // root for the routing tree
  struct p_db *packet_database_root = NULL; // creating packet queue

  init();
  // parsing input table
  rtable_root = parse_rtable(rtable_root);

  while (1) {
    rc = get_packet(&received_packet);
    DIE(rc < 0, "get_message");

    struct ether_header *eth_hdr =
        (struct ether_header *)received_packet.payload;
    struct ether_arp *ether_arp_hdr = NULL;

    // checking message type
    if (ntohs(eth_hdr->ether_type) == ETHERTYPE_IP) {
      // checking ip message type and destination
      int check_iphdr = check_ip_packet(received_packet);

      // the destination is the router, but the message is not ICMP ECHO
      if (check_iphdr == 0) {
        // dropping packet
        continue;
      }

      // the destination is the router and the message is ICMP ECHO
      if (check_iphdr == 1) {
        // sending reply
        reply_icmp_echo(&received_packet);
        continue;
      }

      // otherwise, the packet follows usual forwarding process
      packet_database_root = reply_icmp(
          &packet_q, &received_packet, rtable_root, root, packet_database_root);
      continue;
    }
    // if the message type is arp
    if (ntohs(eth_hdr->ether_type) == ETHERTYPE_ARP) {
      // setting header pointers
      ether_arp_hdr = (struct ether_arp *)(received_packet.payload +
                                           sizeof(struct ether_header));
      struct arphdr *arp_hdr = &(ether_arp_hdr->ea_hdr);
      // creating new address as uint32
      uint32_t saddr = convert_to_addr(ether_arp_hdr->arp_spa, 4);
      // creating new entry
      struct arp_entry *a_entry =
          createEntry(ether_arp_hdr->arp_spa, ether_arp_hdr->arp_sha,
                      received_packet.interface, saddr);

      // checking arp message type
      if (htons(arp_hdr->ar_op) == ARPOP_REQUEST) {
        // if it is a request, we reply with own data
        send_arp_reply(packet_q, a_entry, ether_arp_hdr, &received_packet,
                       rtable_root, eth_hdr);

      } else if (htons(arp_hdr->ar_op) == ARPOP_REPLY) {
        // if it is a reply
        // we create equivalent uint32 address
        uint32_t new_saddr = convert_to_addr(ether_arp_hdr->arp_spa, 4);
        // creating entry
        struct arp_entry *new_entry =
            createEntry(ether_arp_hdr->arp_spa, ether_arp_hdr->arp_sha,
                        received_packet.interface, new_saddr);
        // insert entry into tree
        root = insertNode(root, new_entry);

        // send on hold packets to that address, if there are any
        packet_database_root = respond_to_arp_reply(
            packet_q, ether_arp_hdr, &received_packet, packet_database_root);
      }
    }
  }
}
