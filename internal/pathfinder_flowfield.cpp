// Source Code: https://github.com/hit9/quadtree-pathfinding
// License: BSD. Chao Wang, hit9[At]icloud.com.

#include "pathfinder_flowfield.hpp"

#include <algorithm>
#include <cassert>

namespace qdpf {
namespace internal {

FlowFieldPathFinderImpl::FlowFieldPathFinderImpl(int n) : ffa1(FFA1(n)), ffa2(FFA2(n)) {}

void FlowFieldPathFinderImpl::Reset(const QuadtreeMap* m, int x2, int y2, const Rectangle& dest) {
  // debug mode, checks m, it's nullptr if mapx didn't find one.
  assert(m != nullptr);

  // resets the attributes.
  this->m = m;
  this->x2 = x2, this->y2 = y2;
  this->dest = dest;  // copy updated

  t = m->PackXY(x2, y2);
  tNode = m->FindNode(x2, y2);
  if (tNode == nullptr) return;

  // clears the old results.
  nodeFlowField.Clear();
  gateFlowField.Clear();
  finalFlowField.Clear();

  // Rebuild the tmp graph.
  PathFinderHelper::Reset(this->m);
  // Add the target cell to the gate graph
  bool tIsGate = m->IsGateCell(tNode, t);
  if (!tIsGate) AddCellToNodeOnTmpGraph(t, tNode);

  // Special case:
  // if the target node overlaps the dest rectangle, we should connects the overlaping cells to
  // the target, since the best path is a straight line then.
  Rectangle tNodeRectangle{tNode->x1, tNode->y1, tNode->x2, tNode->y2};
  Rectangle overlap;
  auto hasOverlap = GetOverlap(tNodeRectangle, dest, overlap);
  if (hasOverlap) {
    for (int x = overlap.x1; x <= overlap.x2; ++x) {
      for (int y = overlap.y1; y <= overlap.y2; ++y) {
        int u = m->PackXY(x, y);
        // detail notice is: u should not be a gate cell,
        // since we already connect all gate cells with t.
        if (u != t && m->IsGateCell(tNode, u)) ConnectCellsOnTmpGraph(u, t);
      }
    }
  }
}

int FlowFieldPathFinderImpl::ComputeNodeFlowField() {
  // TODO:
  return 0;
}

int FlowFieldPathFinderImpl::ComputeGateFlowField() {
  // TODO:
  return 0;
}

int FlowFieldPathFinderImpl::ComputeCellFlowFieldInDestRectangle() {
  // TODO:
  return 0;
}

}  // namespace internal
}  // namespace qdpf
