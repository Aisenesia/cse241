package hw3;

import java.util.Iterator;

/**
 * An interface representing a generic container in Java.
 *
 * @param <T> The type of elements in the container.
 */
public interface JavaContainer<T> {
	/**
	 * Adds an element to the container.
	 *
	 * @param element The element to be added.
	 */
	void add(T element);

	/**
	 * Removes an element from the container.
	 *
	 * @param element The element to be removed.
	 */
	void remove(T element);

	/**
	 * Gets the size of the container.
	 *
	 * @return The size of the container.
	 */
	int size();

	/**
	 * Gets an iterator for the container.
	 *
	 * @return An iterator for the container.
	 */
	Iterator<T> getIterator();
}
