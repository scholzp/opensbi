/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 *
 *
 * Authors:
 *   Pascal Scholz
 *
 * The RISC-V SoC on the Icicle Kit is similar to the one used by
 * the SiFive Unleashed.
 *
 */

#include <platform_override.h>
#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/fdt/fdt_fixup.h>

static u64 mpfs_icicle_kit_tlbr_flush_limit(const struct fdt_match *match)
{
	/*
	 * The sfence.vma by virtual address does not work on
	 * SiFive FU540 so we return remote TLB flush limit as zero.
	 */
	return 0;
}

static int mpfs_icicle_kit_fdt_fixup(void *fdt, const struct fdt_match *match)
{
	/*
	 * SiFive Freedom U540 has an erratum that prevents S-mode software
	 * to access a PMP protected region using 1GB page table mapping, so
	 * always add the no-map attribute on this platform.
	 */
	fdt_reserved_memory_nomap_fixup(fdt);

	return 0;
}

static const struct fdt_match mpfs_icicle_kit_match[] = {
	{ .compatible = "microchip,mpfs-icicle-kit" },
	{ .compatible = "microchip,mpfs-icicle-kit-es" },
	{ },
};

const struct platform_override mpfs_icicle_kit = {
	.match_table = mpfs_icicle_kit_match,
	.tlbr_flush_limit = mpfs_icicle_kit_tlbr_flush_limit,
	.fdt_fixup = mpfs_icicle_kit_fdt_fixup,
};
