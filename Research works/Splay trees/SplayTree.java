/*
*   Francisco Javier Blázquez Martínez   ~  frblazqu@ucm.es
*
*   Doble grado en Matemáticas - Ingeniería informática
*   Universidad complutense, Madrid
*
*   Descripción: Implementación de árboles de búsqueda autoajustables.
*/

package ucm.fdi.marp;

public class SplayTree<T extends Comparable<T>>
{
	protected Node root;

	protected class Node
	{
		private T    elem;
		private Node left;
		private Node right;
		private Node parent;

		public Node(Node l, T e, Node r, Node p)
		{
			left   = l;
			elem   = e;
			right  = r;
			parent = p;
		}
	}

	public SplayTree()
	{
		root  = null;
	}
	
	public boolean empty()
	{
		return root == null;
	}
	
	public boolean find(T elem)
	{
	  Node father = null;
	  Node node   = root;

	  while(node != null)
	  {
	    father = node;

	         if(elem.compareTo(node.elem) < 0)     node = node.left;
	    else if(elem.compareTo(node.elem) > 0)     node = node.right;
	    else {splay(node); return true;} // The element is already in the tree
	  }

	  if(father != null)
		  splay(father);

	  return false;
	}
	
	public boolean insert(T elem)
	{
	  Node father = null;
	  Node node = root;

	  while(node != null)
	  {
	    father = node;

	         if(elem.compareTo(node.elem) < 0)     node = node.left;
	    else if(elem.compareTo(node.elem) > 0)     node = node.right;
	    else {splay(node); return false;} // The element is already in the tree
	  }

	  node = new Node(null, elem, null, father);

	  if(father != null)
	    {if(elem.compareTo(father.elem)<0) father.left = node;
	     else                          	   father.right= node;}
	  else
	    root = node;

	  splay(node);  return true;

	}

	public boolean erase(T elem)
	{
	  Node father = null;
	  Node node = root;

	  while(node != null)
	  {
	         if(elem.compareTo(node.elem)<0)   {father = node; node = node.left;}
	    else if(elem.compareTo(node.elem)>0)   {father = node; node = node.right;}
	    else break; // node points to a node with elem inside
	  }

	  if(node == null) {if(father != null) splay(father); return false;}

	  if(node.left == null && node.right == null)   // LEAF CASE
	  {
	    if(node.parent == null) root = null;
	    else
	    {
	    //We want to compare references, not values!! We use '=='
	      if(node == node.parent.left)  node.parent.left = null;
	      else                          node.parent.right= null;
	    }
	  }
	  else if(node.left == null)              // ONLY RIGHT SUBTREE
	  {
	    if(node.parent == null) {root = node.right; root.parent = null;}
	    else
	    {
	      node.right.parent = node.parent;

	      if(node == node.parent.left)  node.parent.left = node.right;
	      else                          node.parent.right= node.right;
	    }
	  }
	  else if(node.right == null)             // ONLY LEFT SUBTREE
	  {
	      if(node.parent == null) {root = node.left;  root.parent = null;}
	      else
	      {
	        node.left.parent = node.parent;

	        if(node == node.parent.left)  node.parent.left = node.left;
	        else                          node.parent.right= node.left;
	      }
	  }
	  else                              // BOTH CHILDREN EXIST
	  {
	    // We get the less greater
	    Node lessGreater = node.right; while(lessGreater.left != null) lessGreater = lessGreater.left;

	    // We 'disconnect' it temporally from its position
	    if(lessGreater.right != null)
	    {
	      lessGreater.right.parent = lessGreater.parent;

	      if(lessGreater == lessGreater.parent.right) lessGreater.parent.right = lessGreater.right;
	      else                                        lessGreater.parent.left  = lessGreater.right;
	    }
	    else
	    {
	      if(lessGreater == lessGreater.parent.right)  lessGreater.parent.right = null;
	      else                                         lessGreater.parent.left  = null;
	    }

	    // We replace node to delete with the less greater element
	    lessGreater.left  = node.left;   if(node.left != null)  node.left.parent = lessGreater;
	    lessGreater.right = node.right;  if(node.right!= null)  node.right.parent= lessGreater;
	    lessGreater.parent= node.parent;

	    if(node.parent != null)
	      {if(node == node.parent.left) node.parent.left = lessGreater;
	       else                         node.parent.right= lessGreater;}
	    else
	      root = lessGreater;
	  }

	  if(father != null)
		  splay(father);

	  return true;
	}
	
	public void    print()
	{
		print(root, 0);
	}
	
	protected void rotateRight(Node node)
	{
		if(node == null)
		    throw new NullPointerException("Right rotation over null node!");

		  Node father    = node.parent;   //Father
		  Node leftChild = node.left;     //Left child

		  if(leftChild != null)
		  {
		    node.left        = leftChild.right;
		    node.parent      = leftChild;
		    leftChild.parent = father;
		    leftChild.right  = node;

		    if(node.left != null)  node.left.parent = node;
		    if(father    != null)
		      {if(node == father.left)  father.left = leftChild;
		       else                     father.right= leftChild;}
		    else
		      root = leftChild;
		  }
	}
	
	protected void rotateLeft(Node node)
	{
		  if(node == null)
			    throw new NullPointerException("Left rotation over null node!");

		  Node father     = node.parent;    //Father
		  Node rightChild = node.right;     //Right child

		  if(rightChild != null)
		  {
		    node.right        = rightChild.left;
		    node.parent       = rightChild;
		    rightChild.parent = father;
		    rightChild.left   = node;

		    if(node.right != null)  node.right.parent = node;
		    if(father      != null)
		      {if(node == father.left)  father.left = rightChild;
		       else                      father.right= rightChild;}
		    else
		      root = rightChild;
		  }
	}

	protected void splay(Node node)
	{
		if(node == null)
		    throw new NullPointerException("Splay over null node!");
		  while(node.parent != null)
		  {
		    if(node.parent.parent == null)  //Direct child from root!
		    {
		      if(node.parent.left == node)  rotateRight(node.parent);
		      else                          rotateLeft(node.parent);
		    }
		    else                            //Node has grandfather
		    {
		      Node grandParent = node.parent.parent;

		      if(grandParent.left != null       && node == grandParent.left.left)    //Zig-zig
		       {rotateRight(grandParent);
		        rotateRight(node.parent);}
		      else if(grandParent.right != null && node == grandParent.right.right)  //Zag-zag
		        {rotateLeft(grandParent);
		         rotateLeft(node.parent);}
		      else if(grandParent.left  != null  && node == grandParent.left.right)   //Zag-Zig
		      	{rotateLeft(node.parent);
		         rotateRight(grandParent);}
		      else if(grandParent.right != null && node == grandParent.right.left)   //Zig-zag
		        {rotateRight(node.parent);
		         rotateLeft(grandParent);}
		      else
		        throw new IllegalStateException("Illegal state reached during splay operation!");
		    }
		  }
	}
	
	public void    print(Node node, int level)
	{
	  if(node != null)
	  {
	    System.out.print(node.elem + ":" + level + " ");

	    print(node.left,  level+1);
	    print(node.right, level+1);
	  }
	}

}
