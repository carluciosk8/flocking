/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
inline const float* TriMesh::getVertexPointer() const
   { return m_fpVertexArray; }


inline const float* TriMesh::getNormalPointer() const
   { return m_fpNormalArray; }


inline const float* TriMesh::getColorPointer() const
   { return m_fpColorArray; }


inline const float* TriMesh::getTxCrdPointer() const
   { return m_fpTxCrdArray; }


inline const unsigned int* TriMesh::getIndexPointer() const
   { return m_uipIndexArray; }


inline unsigned int TriMesh::vertexArraySize() const
   { return m_uiNumVerts; }


inline unsigned int TriMesh::indexArraySize() const
   { return m_uiNumIndxs; }
